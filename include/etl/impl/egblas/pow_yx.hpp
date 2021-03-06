//=======================================================================
// Copyright (c) 2014-2017 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

/*!
 * \file
 * \brief EGBLAS wrappers for the pow_yx operation.
 */

#pragma once

#ifdef ETL_EGBLAS_MODE

#include "etl/impl/cublas/cuda.hpp"

#include <egblas.hpp>

#endif

namespace etl {

namespace impl {

namespace egblas {

/*!
 * \brief Indicates if EGBLAS has single-precision pow_yxarithm.
 */
#ifdef EGBLAS_HAS_SPOW_YX
static constexpr bool has_spow_yx = true;
#else
static constexpr bool has_spow_yx = false;
#endif

/*!
 * \brief Wrappers for single-precision egblas pow_yx operation
 * \param n The size of the vector
 * \param alpha The scaling factor alpha
 * \param A The memory of the vector a
 * \param lda The leading dimension of a
 * \param B The memory of the vector b
 * \param ldb The leading dimension of b
 */
inline void pow_yx(size_t n, float* alpha, float* A , size_t lda, float* B , size_t ldb){
#ifdef EGBLAS_HAS_SPOW_YX
    egblas_spow_yx(n, *alpha, A, lda, B, ldb);
#else
    cpp_unused(n);
    cpp_unused(alpha);
    cpp_unused(A);
    cpp_unused(lda);
    cpp_unused(B);
    cpp_unused(ldb);

    cpp_unreachable("Invalid call to egblas::pow_yx");
#endif
}

/*!
 * \brief Indicates if EGBLAS has double-precision pow_yxarithm.
 */
#ifdef EGBLAS_HAS_DPOW_YX
static constexpr bool has_dpow_yx = true;
#else
static constexpr bool has_dpow_yx = false;
#endif

/*!
 * \brief Wrappers for double-precision egblas pow_yx operation
 * \param n The size of the vector
 * \param alpha The scaling factor alpha
 * \param A The memory of the vector a
 * \param lda The leading dimension of a
 * \param B The memory of the vector b
 * \param ldb The leading dimension of b
 */
inline void pow_yx(size_t n, double* alpha, double* A , size_t lda, double* B , size_t ldb){
#ifdef EGBLAS_HAS_DPOW_YX
    egblas_dpow_yx(n, *alpha, A, lda, B, ldb);
#else
    cpp_unused(n);
    cpp_unused(alpha);
    cpp_unused(A);
    cpp_unused(lda);
    cpp_unused(B);
    cpp_unused(ldb);

    cpp_unreachable("Invalid call to egblas::pow_yx");
#endif
}

/*!
 * \brief Indicates if EGBLAS has complex single-precision pow_yxarithm.
 */
#ifdef EGBLAS_HAS_CPOW_YX
static constexpr bool has_cpow_yx = true;
#else
static constexpr bool has_cpow_yx = false;
#endif

/*!
 * \brief Wrappers for complex single-precision egblas pow_yx operation
 * \param n The size of the vector
 * \param alpha The scaling factor alpha
 * \param A The memory of the vector a
 * \param lda The leading dimension of a
 * \param B The memory of the vector b
 * \param ldb The leading dimension of b
 */
inline void pow_yx(size_t n, std::complex<float>* alpha, std::complex<float>* A , size_t lda, std::complex<float>* B , size_t ldb){
#ifdef EGBLAS_HAS_CPOW_YX
    egblas_cpow_yx(n, *reinterpret_cast<cuComplex*>(alpha), reinterpret_cast<cuComplex*>(A), lda, reinterpret_cast<cuComplex*>(B), ldb);
#else
    cpp_unused(n);
    cpp_unused(alpha);
    cpp_unused(A);
    cpp_unused(lda);
    cpp_unused(B);
    cpp_unused(ldb);

    cpp_unreachable("Invalid call to egblas::pow_yx");
#endif
}

/*!
 * \brief Wrappers for complex single-precision egblas pow_yx operation
 * \param n The size of the vector
 * \param alpha The scaling factor alpha
 * \param A The memory of the vector a
 * \param lda The leading dimension of a
 * \param B The memory of the vector b
 * \param ldb The leading dimension of b
 */
inline void pow_yx(size_t n, etl::complex<float>* alpha, etl::complex<float>* A , size_t lda, etl::complex<float>* B , size_t ldb){
#ifdef EGBLAS_HAS_CPOW_YX
    egblas_cpow_yx(n, *reinterpret_cast<cuComplex*>(alpha), reinterpret_cast<cuComplex*>(A), lda, reinterpret_cast<cuComplex*>(B), ldb);
#else
    cpp_unused(n);
    cpp_unused(alpha);
    cpp_unused(A);
    cpp_unused(lda);
    cpp_unused(B);
    cpp_unused(ldb);

    cpp_unreachable("Invalid call to egblas::pow_yx");
#endif
}

/*!
 * \brief Indicates if EGBLAS has complex double-precision pow_yxarithm.
 */
#ifdef EGBLAS_HAS_ZPOW_YX
static constexpr bool has_zpow_yx = true;
#else
static constexpr bool has_zpow_yx = false;
#endif

/*!
 * \brief Wrappers for complex double-precision egblas pow_yx operation
 * \param n The size of the vector
 * \param alpha The scaling factor alpha
 * \param A The memory of the vector a
 * \param lda The leading dimension of a
 * \param B The memory of the vector b
 * \param ldb The leading dimension of b
 */
inline void pow_yx(size_t n, std::complex<double>* alpha, std::complex<double>* A , size_t lda, std::complex<double>* B , size_t ldb){
#ifdef EGBLAS_HAS_ZPOW_YX
    egblas_zpow_yx(n, *reinterpret_cast<cuDoubleComplex*>(alpha), reinterpret_cast<cuDoubleComplex*>(A), lda, reinterpret_cast<cuDoubleComplex*>(B), ldb);
#else
    cpp_unused(n);
    cpp_unused(alpha);
    cpp_unused(A);
    cpp_unused(lda);
    cpp_unused(B);
    cpp_unused(ldb);

    cpp_unreachable("Invalid call to egblas::pow_yx");
#endif
}

/*!
 * \brief Wrappers for complex double-precision egblas pow_yx operation
 * \param n The size of the vector
 * \param alpha The scaling factor alpha
 * \param A The memory of the vector a
 * \param lda The leading dimension of a
 * \param B The memory of the vector b
 * \param ldb The leading dimension of b
 */
inline void pow_yx(size_t n, etl::complex<double>* alpha, etl::complex<double>* A , size_t lda, etl::complex<double>* B , size_t ldb){
#ifdef EGBLAS_HAS_ZPOW_YX
    egblas_zpow_yx(n, *reinterpret_cast<cuDoubleComplex*>(alpha), reinterpret_cast<cuDoubleComplex*>(A), lda, reinterpret_cast<cuDoubleComplex*>(B), ldb);
#else
    cpp_unused(n);
    cpp_unused(alpha);
    cpp_unused(A);
    cpp_unused(lda);
    cpp_unused(B);
    cpp_unused(ldb);

    cpp_unreachable("Invalid call to egblas::pow_yx");
#endif
}

} //end of namespace egblas
} //end of namespace impl
} //end of namespace etl
