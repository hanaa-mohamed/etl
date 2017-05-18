//=======================================================================
// Copyright (c) 2014-2017 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#pragma once

#include "etl/expr/base_temporary_expr.hpp"

//Get the implementations
#include "etl/impl/conv.hpp"

namespace etl {

/*!
 * \brief Expression representing a batch of transposed 2D convolution of an
 * batch of image with a set of kernel.
 *
 * The configuration (padding and stride) is the configuration of
 * the convolution that is to be transposed.
 *
 * The padding is transposed as the reverse amount of padding to
 * obtain the correct size.
 *
 * The stride is transposed as a fractionally strided convolution
 * with inner padding.
 *
 * For in an input of [WxH] dimensions and a kernel [K1xK1], the output will be
 * a 2D matrix of dimensions [W'xH'] with:
 *  W' = S1 * (W - 1) + K1 - 2 * P1
 *  H' = S2 * (H - 1) + K2 - 2 * P2
 *
 * \tparam A The input type
 * \tparam B The kernel type
 * \tparam Flipped Indicates if Flipped already or not or not
 */
template <typename A, typename B, bool Flipped>
struct dyn_conv_4d_backward_expr : base_temporary_expr_bin<dyn_conv_4d_backward_expr<A, B, Flipped>, A, B> {
    using value_type  = value_t<A>;                               ///< The type of value of the expression
    using this_type   = dyn_conv_4d_backward_expr<A, B, Flipped>; ///< The type of this expression
    using base_type   = base_temporary_expr_bin<this_type, A, B>; ///< The base type
    using left_traits = decay_traits<A>;                          ///< The traits of the sub type

    static constexpr auto storage_order = left_traits::storage_order; ///< The sub storage order

    const size_t s1; ///< The stride of the first dimension
    const size_t s2; ///< The stride of the second dimension
    const size_t p1; ///< The padding of the first dimension
    const size_t p2; ///< The padding of the second dimension

    /*!
     * \brief Construct a new expression
     * \param a The sub expression
     */
    explicit dyn_conv_4d_backward_expr(A a, B b, size_t s1, size_t s2, size_t p1, size_t p2) : base_type(a, b), s1(s1), s2(s2), p1(p1), p2(p2) {
        //Nothing else to init
    }

    // Assignment functions

    /*!
     * \brief Assert that the convolution is done on correct dimensions
     */
    template <typename I, typename K, typename C>
    void check(const I& input, const K& kernel, const C& conv) const {
        static_assert(etl::dimensions<I>() == 4, "Invalid number of dimensions for input of conv4_backward");
        static_assert(etl::dimensions<K>() == 4, "Invalid number of dimensions for kernel of conv4_backward");
        static_assert(etl::dimensions<C>() == 4, "Invalid number of dimensions for conv of conv4_backward");

        cpp_assert(etl::dim(conv, 0) == etl::dim(input, 0), "Invalid dimensions for conv4_backward");
        cpp_assert(etl::dim(conv, 1) == etl::dim(kernel, 1), "Invalid dimensions for conv4_backward");
        cpp_assert(etl::dim(input, 1) == etl::dim(kernel, 0), "Invalid dimensions for conv4_backward");

        cpp_assert(etl::dim(conv, 2) == s1 * (etl::dim(input, 2) - 1) + etl::dim(kernel, 2) - 2 * p1, "Invalid dimensions for conv2_backward");
        cpp_assert(etl::dim(conv, 3) == s2 * (etl::dim(input, 3) - 1) + etl::dim(kernel, 3) - 2 * p2, "Invalid dimensions for conv2_backward");

        cpp_unused(input);
        cpp_unused(kernel);
        cpp_unused(conv);
    }

    /*!
     * \brief Assign to a matrix
     * \param c The expression to which assign
     */
    template<typename C>
    void assign_to(C&& c)  const {
        static_assert(all_etl_expr<A, B, C>::value, "conv4_backward only supported for ETL expressions");

        auto& a = this->a();
        auto& b = this->b();

        check(a, b, c);

        standard_evaluator::pre_assign_rhs(a);
        standard_evaluator::pre_assign_rhs(b);

        if /* constexpr */ (Flipped){
            detail::dyn_conv4_backward_flipped_impl::apply(make_temporary(a), make_temporary(b), c, s1, s2, p1, p2);
        } else {
            detail::dyn_conv4_backward_impl::apply(make_temporary(a), make_temporary(b), c, s1, s2, p1, p2);
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
    friend std::ostream& operator<<(std::ostream& os, const dyn_conv_4d_backward_expr& expr) {
        return os << "conv4_backward(" << expr._a << ", " << expr._b << ")";
    }
};

/*!
 * \brief Traits for a transpose expression
 * \tparam A The transposed sub type
 */
template <typename A, typename B, bool Flipped>
struct etl_traits<etl::dyn_conv_4d_backward_expr<A, B, Flipped>> {
    using expr_t       = etl::dyn_conv_4d_backward_expr<A, B, Flipped>; ///< The expression type
    using left_expr_t  = std::decay_t<A>;                               ///< The left sub expression type
    using right_expr_t = std::decay_t<B>;                               ///< The right sub expression type
    using left_traits  = etl_traits<left_expr_t>;                       ///< The left sub traits
    using right_traits = etl_traits<right_expr_t>;                      ///< The right sub traits
    using value_type   = value_t<A>;                                    ///< The value type of the expression

    static constexpr bool is_etl          = true;                       ///< Indicates if the type is an ETL expression
    static constexpr bool is_transformer  = false;                      ///< Indicates if the type is a transformer
    static constexpr bool is_view         = false;                      ///< Indicates if the type is a view
    static constexpr bool is_magic_view   = false;                      ///< Indicates if the type is a magic view
    static constexpr bool is_fast         = false;                      ///< Indicates if the expression is fast
    static constexpr bool is_linear       = true;                       ///< Indicates if the expression is linear
    static constexpr bool is_thread_safe  = true;                       ///< Indicates if the expression is thread safe
    static constexpr bool is_value        = false;                      ///< Indicates if the expression is of value type
    static constexpr bool is_direct       = true;                       ///< Indicates if the expression has direct memory access
    static constexpr bool is_generator    = false;                      ///< Indicates if the expression is a generator
    static constexpr bool is_padded       = false;                      ///< Indicates if the expression is padded
    static constexpr bool is_aligned      = true;                       ///< Indicates if the expression is padded
    static constexpr bool is_gpu          = false;                      ///< Indicates if the expression can be done on GPU
    static constexpr bool is_temporary = true;                       ///< Indicates if the expression needs a evaluator visitor
    static constexpr order storage_order  = left_traits::storage_order; ///< The expression's storage order

    /*!
     * \brief Indicates if the expression is vectorizable using the
     * given vector mode
     * \tparam V The vector mode
     */
    template <vector_mode_t V>
    using vectorizable = std::true_type;

    /*!
     * \brief Returns the dth dimension of the expression
     * \param e The sub expression
     * \param d The dimension to get
     * \return the dth dimension of the expression
     */
    static size_t dim(const expr_t& e, size_t d) {
        if (d == 0){
            return etl::dim(e._a, 0);
        } else if (d == 1){
            return etl::dim(e._b, 1);
        } else if (d == 2){
            return e.s1 * (etl::dim(e._a, 2) - 1) + etl::dim(e._b, 2) - 2 * e.p1;
        } else {
            return e.s2 * (etl::dim(e._a, 3) - 1) + etl::dim(e._b, 3) - 2 * e.p2;
        }
    }

    /*!
     * \brief Returns the size of the expression
     * \param e The sub expression
     * \return the size of the expression
     */
    static size_t size(const expr_t& e) {
        return etl::dim(e._a, 0) * etl::dim(e._b, 1) * (e.s1 * (etl::dim(e._a, 2) - 1) + etl::dim(e._b, 2) - 2 * e.p1) *
               (e.s2 * (etl::dim(e._a, 3) - 1) + etl::dim(e._b, 3) - 2 * e.p2);
    }

    /*!
     * \brief Returns the number of dimensions of the expression
     * \return the number of dimensions of the expression
     */
    static constexpr size_t dimensions() {
        return 4;
    }
};

/*!
 * \brief Creates an expression representing the transposed 2D convolution of a and b.
 *
 * The 4D matrix a is assumed to be of [N, C, H, W] dimensions.
 * The 4D matrix b is assumed to be of [K, C, H, W] dimensions.
 *
 * \param a The input expression
 * \param b The kernel expression
 *
 * \return an expression representing the transposed convolution convolution of a and b
 */
template <typename A, typename B>
dyn_conv_4d_backward_expr<detail::build_type<A>, detail::build_type<B>, false>
conv_4d_backward(A&& a, B&& b, size_t s1, size_t s2, size_t p1, size_t p2) {
    static_assert(all_etl_expr<A, B>::value, "Convolution only supported for ETL expressions");

    return dyn_conv_4d_backward_expr<detail::build_type<A>, detail::build_type<B>, false>{a, b, s1, s2, p1, p2};
}

/*!
 * \brief Creates an expression representing the transposed 2D convolution of a and b, the result will be stored in c
 *
 * The 4D matrix a is assumed to be of [N, C, Hi, Wi] dimensions.
 * The 4D matrix b is assumed to be of [K, C, Hf, Wf] dimensions.
 * The 4D matrix c is assumed to be of [N, K, Hi - Hf + 1, Wi - Wf + 1] dimensions.
 *
 * \param a The input expression
 * \param b The kernel expression
 * \param c The result
 *
 * \return an expression representing the transposed 2D convolution of a and b
 */
template <typename A, typename B, typename C>
auto conv_4d_backward(A&& a, B&& b, C&& c, size_t s1, size_t s2, size_t p1, size_t p2){
    static_assert(all_etl_expr<A, B, C>::value, "Convolution only supported for ETL expressions");

    c = conv_4d_backward(a, b, s1, s2, p1, p2);

    return c;
}

/*!
 * \brief Creates an expression representing the transposed 2D convolution of a and flipped b.
 *
 * The 4D matrix a is assumed to be of [N, C, H, W] dimensions.
 * The 4D matrix b is assumed to be of [K, C, H, W] dimensions.
 *
 * \param a The input expression
 * \param b The kernel expression
 *
 * \return an expression representing the transposed 2D convolution of a and b
 */
template <typename A, typename B>
dyn_conv_4d_backward_expr<detail::build_type<A>, detail::build_type<B>, true>
conv_4d_backward_flipped(A&& a, B&& b, size_t s1, size_t s2, size_t p1, size_t p2) {
    static_assert(all_etl_expr<A, B>::value, "Convolution only supported for ETL expressions");

    return dyn_conv_4d_backward_expr<detail::build_type<A>, detail::build_type<B>, true>{a, b, s1, s2, p1, p2};
}

/*!
 * \brief Creates an expression representing the transposed 2D convolution of a and flipped b, the result will be stored in c
 *
 * The 4D matrix a is assumed to be of [N, C, Hi, Wi] dimensions.
 * The 4D matrix b is assumed to be of [K, C, Hf, Wf] dimensions.
 * The 4D matrix c is assumed to be of [N, K, Hi - Hf + 1, Wi - Wf + 1] dimensions.
 *
 * \param a The input expression
 * \param b The kernel expression
 * \param c The result
 *
 * \return an expression representing the transposed 2D convolution of a and b
 */
template <typename A, typename B, typename C>
auto conv_4d_backward_flipped(A&& a, B&& b, C&& c, size_t s1, size_t s2, size_t p1, size_t p2){
    static_assert(all_etl_expr<A, B, C>::value, "Convolution only supported for ETL expressions");

    c = conv_4d_backward_flipped(a, b, s1, s2, p1, p2);

    return c;
}

} //end of namespace etl
