//=======================================================================
// Copyright (c) 2014-2017 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

/*!
 * \file
 * \brief EGBLAS wrappers for the conj operation.
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
 * \brief Indicates if EGBLAS has complex single-precision conj.
 */
#ifdef EGBLAS_HAS_CCONJ
static constexpr bool has_cconj = true;
#else
static constexpr bool has_cconj = false;
#endif

/*!
 * \brief Wrappers for complex single-precision egblas conj operation
 * \param n The size of the vector
 * \param alpha The scaling factor alpha
 * \param A The memory of the vector a
 * \param lda The leading dimension of a
 * \param B The memory of the vector b
 * \param ldb The leading dimension of b
 */
inline void conj(size_t n, std::complex<float>* alpha, std::complex<float>* A , size_t lda, std::complex<float>* B , size_t ldb){
#ifdef EGBLAS_HAS_CCONJ
    egblas_cconj(n, *reinterpret_cast<cuComplex*>(alpha), reinterpret_cast<cuComplex*>(A), lda, reinterpret_cast<cuComplex*>(B), ldb);
#else
    cpp_unused(n);
    cpp_unused(alpha);
    cpp_unused(A);
    cpp_unused(lda);
    cpp_unused(B);
    cpp_unused(ldb);

    cpp_unreachable("Invalid call to egblas::conj");
#endif
}

/*!
 * \brief Wrappers for complex single-precision egblas conj operation
 * \param n The size of the vector
 * \param alpha The scaling factor alpha
 * \param A The memory of the vector a
 * \param lda The leading dimension of a
 * \param B The memory of the vector b
 * \param ldb The leading dimension of b
 */
inline void conj(size_t n, etl::complex<float>* alpha, etl::complex<float>* A , size_t lda, etl::complex<float>* B , size_t ldb){
#ifdef EGBLAS_HAS_CCONJ
    egblas_cconj(n, *reinterpret_cast<cuComplex*>(alpha), reinterpret_cast<cuComplex*>(A), lda, reinterpret_cast<cuComplex*>(B), ldb);
#else
    cpp_unused(n);
    cpp_unused(alpha);
    cpp_unused(A);
    cpp_unused(lda);
    cpp_unused(B);
    cpp_unused(ldb);

    cpp_unreachable("Invalid call to egblas::conj");
#endif
}

/*!
 * \brief Indicates if EGBLAS has complex double-precision conj.
 */
#ifdef EGBLAS_HAS_Zconj
static constexpr bool has_zconj = true;
#else
static constexpr bool has_zconj = false;
#endif

/*!
 * \brief Wrappers for complex double-precision egblas conj operation
 * \param n The size of the vector
 * \param alpha The scaling factor alpha
 * \param A The memory of the vector a
 * \param lda The leading dimension of a
 * \param B The memory of the vector b
 * \param ldb The leading dimension of b
 */
inline void conj(size_t n, std::complex<double>* alpha, std::complex<double>* A , size_t lda, std::complex<double>* B , size_t ldb){
#ifdef EGBLAS_HAS_Zconj
    egblas_zconj(n, *reinterpret_cast<cuDoubleComplex*>(alpha), reinterpret_cast<cuDoubleComplex*>(A), lda, reinterpret_cast<cuDoubleComplex*>(B), ldb);
#else
    cpp_unused(n);
    cpp_unused(alpha);
    cpp_unused(A);
    cpp_unused(lda);
    cpp_unused(B);
    cpp_unused(ldb);

    cpp_unreachable("Invalid call to egblas::conj");
#endif
}

/*!
 * \brief Wrappers for complex double-precision egblas conj operation
 * \param n The size of the vector
 * \param alpha The scaling factor alpha
 * \param A The memory of the vector a
 * \param lda The leading dimension of a
 * \param B The memory of the vector b
 * \param ldb The leading dimension of b
 */
inline void conj(size_t n, etl::complex<double>* alpha, etl::complex<double>* A , size_t lda, etl::complex<double>* B , size_t ldb){
#ifdef EGBLAS_HAS_Zconj
    egblas_zconj(n, *reinterpret_cast<cuDoubleComplex*>(alpha), reinterpret_cast<cuDoubleComplex*>(A), lda, reinterpret_cast<cuDoubleComplex*>(B), ldb);
#else
    cpp_unused(n);
    cpp_unused(alpha);
    cpp_unused(A);
    cpp_unused(lda);
    cpp_unused(B);
    cpp_unused(ldb);

    cpp_unreachable("Invalid call to egblas::conj");
#endif
}

} //end of namespace egblas
} //end of namespace impl
} //end of namespace etl
