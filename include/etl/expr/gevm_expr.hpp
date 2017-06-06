//=======================================================================
// Copyright (c) 2014-2017 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#pragma once

#include "etl/expr/base_temporary_expr.hpp"

//The implementations
#include "etl/impl/std/gemm.hpp"
#include "etl/impl/blas/gemm.hpp"
#include "etl/impl/vec/gevm.hpp"
#include "etl/impl/vec/gemm_conv.hpp"
#include "etl/impl/cublas/gemm.hpp"

namespace etl {

/*!
 * \brief A transposition expression.
 * \tparam A The transposed type
 */
template <typename A, typename B>
struct gevm_expr : base_temporary_expr_bin<gevm_expr<A, B>, A, B> {
    using value_type  = value_t<A>;                              ///< The type of value of the expression
    using this_type   = gevm_expr<A, B>;                         ///< The type of this expression
    using base_type   = base_temporary_expr_bin<this_type, A, B>; ///< The base type
    using left_traits = decay_traits<A>;                         ///< The traits of the sub type

    static constexpr auto storage_order = left_traits::storage_order; ///< The sub storage order

    /*!
     * \brief Construct a new expression
     * \param a The sub expression
     */
    explicit gevm_expr(A a, B b) : base_type(a, b) {
        //Nothing else to init
    }

    /*!
     * \brief Assert for the validity of the matrix-matrix multiplication operation
     * \param a The left side matrix
     * \param b The right side matrix
     * \param c The result matrix
     */
    template <typename C, cpp_disable_if(all_fast<A, B, C>::value)>
    static void check(const A& a, const B& b, const C& c) {
        cpp_assert(
            dim<0>(a) == dim<0>(b)         //exterior dimension 1
                && dim<1>(b) == dim<0>(c), //exterior dimension 2
            "Invalid sizes for multiplication");
        cpp_unused(a);
        cpp_unused(b);
        cpp_unused(c);
    }

    /*!
     * \brief Assert for the validity of the matrix-matrix multiplication operation
     * \param a The left side matrix
     * \param b The right side matrix
     * \param c The result matrix
     */
    template <typename C, cpp_enable_if(all_fast<A, B, C>::value)>
    static void check(const A& a, const B& b, const C& c) {
        static_assert(
            dim<0, A>() == dim<0, B>()         //exterior dimension 1
                && dim<1, B>() == dim<0, C>(), //exterior dimension 2
            "Invalid sizes for multiplication");
        cpp_unused(a);
        cpp_unused(b);
        cpp_unused(c);
    }

    // Assignment functions

    /*!
     * \brief Select an implementation of GEVM, not considering local context
     * \param n1 The left dimension of the  multiplication
     * \param n2 The right dimension of the  multiplication
     * \return The implementation to use
     */
    template <typename C>
    static inline cpp14_constexpr gemm_impl select_default_gevm_impl(const size_t n1, const size_t n2) {
        using T = value_t<A>;

        constexpr bool vec_possible = all_vectorizable_t<vector_mode, A, B, C>::value && vec_enabled;

        if(cblas_enabled){
            if(vec_possible && n1 * n2 <= 200 * 200){
                return gemm_impl::VEC;
            }

            return gemm_impl::BLAS;
        }

        if(vec_possible){
            return gemm_impl::VEC;
        }

        if (cublas_enabled && is_complex_single_t<T>::value && n1 * n2 > 1000 * 1000) {
            return gemm_impl::CUBLAS;
        }

        return gemm_impl::STD;
    }

    /*!
     * \brief Select an implementation of GEVM
     * \param n1 The left dimension of the  multiplication
     * \param n2 The right dimension of the  multiplication
     * \return The implementation to use
     */
    template <typename C>
    static inline gemm_impl select_gevm_impl(const size_t n1, const size_t n2) {
        if (local_context().gemm_selector.forced) {
            auto forced = local_context().gemm_selector.impl;

            switch (forced) {
                //CUBLAS cannot always be used
                case gemm_impl::CUBLAS:
                    if (!cublas_enabled) {                                                                                                //COVERAGE_EXCLUDE_LINE
                        std::cerr << "Forced selection to CUBLAS gevm implementation, but not possible for this expression" << std::endl; //COVERAGE_EXCLUDE_LINE
                        return select_default_gevm_impl<C>(n1, n2);                                                                       //COVERAGE_EXCLUDE_LINE
                    }                                                                                                                     //COVERAGE_EXCLUDE_LINE

                    return forced;

                //BLAS cannot always be used
                case gemm_impl::BLAS:
                    if (!cblas_enabled) {                                                                                               //COVERAGE_EXCLUDE_LINE
                        std::cerr << "Forced selection to BLAS gevm implementation, but not possible for this expression" << std::endl; //COVERAGE_EXCLUDE_LINE
                        return select_default_gevm_impl<C>(n1, n2);                                                                     //COVERAGE_EXCLUDE_LINE
                    }                                                                                                                   //COVERAGE_EXCLUDE_LINE

                    return forced;

                //VEC cannot always be used
                case gemm_impl::VEC:
                    if (!vec_enabled || !all_vectorizable<vector_mode, A, B, C>::value) {                                              //COVERAGE_EXCLUDE_LINE
                        std::cerr << "Forced selection to VEC gemv implementation, but not possible for this expression" << std::endl; //COVERAGE_EXCLUDE_LINE
                        return select_default_gevm_impl<C>(n1, n2);                                                                  //COVERAGE_EXCLUDE_LINE
                    }                                                                                                                  //COVERAGE_EXCLUDE_LINE

                    return forced;

                //In other cases, simply use the forced impl
                default:
                    return forced;
            }
        }

        return select_default_gevm_impl<C>(n1, n2);
    }

    /*!
     * \brief Assign to a matrix of the same storage order
     * \param c The expression to which assign
     */
    template<typename C>
    void assign_to(C&& c)  const {
        static_assert(all_etl_expr<A, B, C>::value, "gemm only supported for ETL expressions");

        auto& a = this->a();
        auto& b = this->b();

        check(a, b, c);

        standard_evaluator::pre_assign_rhs(a);
        standard_evaluator::pre_assign_rhs(b);

        auto impl = select_gevm_impl<C>(etl::dim<0>(b), etl::dim<1>(b));

        if (impl == gemm_impl::STD) {
            etl::impl::standard::vm_mul(make_temporary(a), make_temporary(b), c);
        } else if (impl == gemm_impl::BLAS) {
            etl::impl::blas::gevm(make_temporary(a), make_temporary(b), c);
        } else if (impl == gemm_impl::VEC) {
            etl::impl::vec::gevm(make_temporary(a), make_temporary(b), c);
        } else if (impl == gemm_impl::CUBLAS) {
            etl::impl::cublas::gevm(make_temporary(a), make_temporary(b), c);
        } else {
            cpp_unreachable("Invalid selection for gevm");
        }
    }

    /*!
     * \brief Add to the given left-hand-side expression
     * \param lhs The expression to which assign
     */
    template<typename L>
    void assign_add_to(L&& lhs)  const {
        std_add_evaluate(*this, lhs);
    }

    /*!
     * \brief Sub from the given left-hand-side expression
     * \param lhs The expression to which assign
     */
    template<typename L>
    void assign_sub_to(L&& lhs)  const {
        std_sub_evaluate(*this, lhs);
    }

    /*!
     * \brief Multiply the given left-hand-side expression
     * \param lhs The expression to which assign
     */
    template<typename L>
    void assign_mul_to(L&& lhs)  const {
        std_mul_evaluate(*this, lhs);
    }

    /*!
     * \brief Divide the given left-hand-side expression
     * \param lhs The expression to which assign
     */
    template<typename L>
    void assign_div_to(L&& lhs)  const {
        std_div_evaluate(*this, lhs);
    }

    /*!
     * \brief Modulo the given left-hand-side expression
     * \param lhs The expression to which assign
     */
    template<typename L>
    void assign_mod_to(L&& lhs)  const {
        std_mod_evaluate(*this, lhs);
    }

    /*!
     * \brief Print a representation of the expression on the given stream
     * \param os The output stream
     * \param expr The expression to print
     * \return the output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const gevm_expr& expr) {
        return os << expr._a << " * " << expr._b;
    }
};

/*!
 * \brief Traits for a transpose expression
 * \tparam A The transposed sub type
 */
template <typename A, typename B>
struct etl_traits<etl::gevm_expr<A, B>> {
    using expr_t       = etl::gevm_expr<A, B>;     ///< The expression type
    using left_expr_t  = std::decay_t<A>;          ///< The left sub expression type
    using right_expr_t = std::decay_t<B>;          ///< The right sub expression type
    using left_traits  = etl_traits<left_expr_t>;  ///< The left sub traits
    using right_traits = etl_traits<right_expr_t>; ///< The right sub traits
    using value_type   = value_t<A>;               ///< The value type of the expression

    static constexpr bool is_etl                  = true;                                          ///< Indicates if the type is an ETL expression
    static constexpr bool is_transformer          = false;                                         ///< Indicates if the type is a transformer
    static constexpr bool is_view                 = false;                                         ///< Indicates if the type is a view
    static constexpr bool is_magic_view           = false;                                         ///< Indicates if the type is a magic view
    static constexpr bool is_fast                 = left_traits::is_fast && right_traits::is_fast; ///< Indicates if the expression is fast
    static constexpr bool is_linear               = false;                                          ///< Indicates if the expression is linear
    static constexpr bool is_thread_safe          = true;                                          ///< Indicates if the expression is thread safe
    static constexpr bool is_value                = false;                                         ///< Indicates if the expression is of value type
    static constexpr bool is_direct               = true;                                          ///< Indicates if the expression has direct memory access
    static constexpr bool is_generator            = false;                                         ///< Indicates if the expression is a generator
    static constexpr bool is_padded               = false;                                         ///< Indicates if the expression is padded
    static constexpr bool is_aligned              = true;                                          ///< Indicates if the expression is padded
    static constexpr bool is_gpu                  = false;                                         ///< Indicates if the expression can be done on GPU
    static constexpr bool is_temporary = true;                                          ///< Indicates if the expression needs a evaluator visitor
    static constexpr order storage_order          = left_traits::storage_order;                     ///< The expression's storage order

    /*!
     * \brief Indicates if the expression is vectorizable using the
     * given vector mode
     * \tparam V The vector mode
     */
    template <vector_mode_t V>
    using vectorizable = std::true_type;

    /*!
     * \brief Returns the DDth dimension of the expression
     * \return the DDth dimension of the expression
     */
    template <size_t DD>
    static constexpr size_t dim() {
        return decay_traits<B>::template dim<1>();
    }

    /*!
     * \brief Returns the dth dimension of the expression
     * \param e The sub expression
     * \param d The dimension to get
     * \return the dth dimension of the expression
     */
    static size_t dim(const expr_t& e, size_t d) {
        cpp_unused(d);
        return etl::dim(e._b, 1);
    }

    /*!
     * \brief Returns the size of the expression
     * \param e The sub expression
     * \return the size of the expression
     */
    static size_t size(const expr_t& e) {
        return etl::dim(e._b, 1);
    }

    /*!
     * \brief Returns the size of the expression
     * \return the size of the expression
     */
    static constexpr size_t size() {
        return decay_traits<B>::template dim<1>();
    }

    /*!
     * \brief Returns the number of dimensions of the expression
     * \return the number of dimensions of the expression
     */
    static constexpr size_t dimensions() {
        return 1;
    }
};

/*!
 * \brief Multiply a vector and a matrix together
 * \param a The left hand side vector
 * \param b The right hand side matrix
 * \return An expression representing the vector-matrix multiplication of a and b
 */
template <typename A, typename B, cpp_enable_if(is_1d<A>::value, is_2d<B>::value)>
gevm_expr<detail::build_type<A>, detail::build_type<B>> operator*(A&& a, B&& b) {
    return gevm_expr<detail::build_type<A>, detail::build_type<B>>{a, b};
}

/*!
 * \brief Multiply a vector and a matrix together
 * \param a The left hand side vector
 * \param b The right hand side matrix
 * \return An expression representing the vector-matrix multiplication of a and b
 */
template <typename A, typename B, cpp_enable_if(is_1d<A>::value, is_2d<B>::value)>
gevm_expr<detail::build_type<A>, detail::build_type<B>> mul(A&& a, B&& b) {
    return gevm_expr<detail::build_type<A>, detail::build_type<B>>{a, b};
}

/*!
 * \brief Multiply a vector and a matrix together and store the result in c
 * \param a The left hand side vector
 * \param b The right hand side matrix
 * \param c The expression used to store the result
 * \return An expression representing the vector-matrix multiplication of a and b
 */
template <typename A, typename B, typename C, cpp_enable_if(is_1d<A>::value, is_2d<B>::value)>
auto mul(A&& a, B&& b, C&& c){
    c = mul(a, b);
    return c;
}

} //end of namespace etl
