//=======================================================================
// Copyright (c) 2014-2017 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

/*!
 * \file
 * \brief EGBLAS wrappers for the scalar_div operation.
 */

#pragma once

#ifdef ETL_EGBLAS_MODE

#include "etl/impl/cublas/cuda.hpp"

#include <egblas.hpp>

#endif

namespace etl {

namespace impl {

namespace egblas {

#ifdef EGBLAS_HAS_SCALAR_SDIV

static constexpr bool has_scalar_sdiv = true;

/*!
 * \brief Divide the scalar beta by each element of the single-precision vector x
 * \param beta The scalar to be divide
 * \param x The vector to divide the scalar by (GPU pointer)
 * \param n The size of the vector
 * \param s The stride of the vector
 */
inline void scalar_div(float* beta, float* x, size_t n, size_t s){
    egblas_scalar_sdiv(*beta, x, n, s);
}

#else

static constexpr bool has_scalar_sdiv = false;

#endif

#ifdef EGBLAS_HAS_SCALAR_DDIV

static constexpr bool has_scalar_ddiv = true;

/*!
 * \brief Divide the scalar beta by each element of the single-precision vector x
 * \param beta The scalar to be divide
 * \param x The vector to divide the scalar by (GPU pointer)
 * \param n The size of the vector
 * \param s The stride of the vector
 */
inline void scalar_div(double* beta, double* x, size_t n, size_t s){
    egblas_scalar_ddiv(*beta, x, n, s);
}

#else

static constexpr bool has_scalar_ddiv = false;

#endif

#ifndef ETL_EGBLAS_MODE

/*!
 * \brief Divide the scalar beta by each element of the single-precision vector x
 * \param beta The scalar to be divide
 * \param x The vector to divide the scalar by (GPU pointer)
 * \param n The size of the vector
 * \param s The stride of the vector
 */
template<typename T>
inline void scalar_div(T* beta, T* x, size_t n, size_t s){
    cpp_unused(x);
    cpp_unused(n);
    cpp_unused(s);
    cpp_unused(beta);

    cpp_unreachable("Invalid call to egblas::scalar_div");
}

#endif

} //end of namespace egblas
} //end of namespace impl
} //end of namespace etl
