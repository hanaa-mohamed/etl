//=======================================================================
// Copyright (c) 2014-2016 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

/*!
 * \file avx_vectorization.hpp
 * \brief Contains AVX vectorized functions for the vectorized assignment of expressions
 */

#pragma once

#ifdef __AVX__

#include <immintrin.h>
#include <emmintrin.h>
#include <xmmintrin.h>

#include "etl/avx_exp.hpp"

#ifdef VECT_DEBUG
#include <iostream>
#endif

#define ETL_INLINE_VEC_VOID ETL_STATIC_INLINE(void)
#define ETL_INLINE_VEC_256 ETL_STATIC_INLINE(__m256)
#define ETL_INLINE_VEC_256D ETL_STATIC_INLINE(__m256d)
#define ETL_OUT_VEC_256 ETL_OUT_INLINE(__m256)
#define ETL_OUT_VEC_256D ETL_OUT_INLINE(__m256d)

namespace etl {

/*!
 * \brief Define traits to get vectorization information for types in AVX vector mode.
 */
template <typename T>
struct avx_intrinsic_traits {
    static constexpr const bool vectorizable     = false;      ///< Boolean flag indicating if the type is vectorizable or not
    static constexpr const std::size_t size      = 1;          ///< Numbers of elements done at once
    static constexpr const std::size_t alignment = alignof(T); ///< Necessary number of bytes of alignment for this type

    using intrinsic_type = T;
};

template <>
struct avx_intrinsic_traits<float> {
    static constexpr const bool vectorizable     = true;
    static constexpr const std::size_t size      = 8;
    static constexpr const std::size_t alignment = 32;

    using intrinsic_type = __m256;
};

template <>
struct avx_intrinsic_traits<double> {
    static constexpr const bool vectorizable     = true;
    static constexpr const std::size_t size      = 4;
    static constexpr const std::size_t alignment = 32;

    using intrinsic_type = __m256d;
};

template <>
struct avx_intrinsic_traits<std::complex<float>> {
    static constexpr const bool vectorizable     = true;
    static constexpr const std::size_t size      = 4;
    static constexpr const std::size_t alignment = 32;

    using intrinsic_type = __m256;
};

template <>
struct avx_intrinsic_traits<std::complex<double>> {
    static constexpr const bool vectorizable     = true;
    static constexpr const std::size_t size      = 2;
    static constexpr const std::size_t alignment = 32;

    using intrinsic_type = __m256d;
};

template <>
struct avx_intrinsic_traits<etl::complex<float>> {
    static constexpr const bool vectorizable     = true;
    static constexpr const std::size_t size      = 4;
    static constexpr const std::size_t alignment = 32;

    using intrinsic_type = __m256;
};

template <>
struct avx_intrinsic_traits<etl::complex<double>> {
    static constexpr const bool vectorizable     = true;
    static constexpr const std::size_t size      = 2;
    static constexpr const std::size_t alignment = 32;

    using intrinsic_type = __m256d;
};

struct avx_vec {
    template <typename T>
    using traits = avx_intrinsic_traits<T>;

    template <typename T>
    using vec_type = typename traits<T>::intrinsic_type;

#ifdef VEC_DEBUG

    template <typename T>
    static std::string debug_d(T value) {
        union test {
            __m256d vec; // a data field, maybe a register, maybe not
            double array[4];
            test(__m256d vec)
                    : vec(vec) {}
        };

        test u_value = value;
        std::cout << "[" << u_value.array[0] << "," << u_value.array[1] << "," << u_value.array[2] << "," << u_value.array[3] << "]" << std::endl;
    }

    template <typename T>
    static std::string debug_s(T value) {
        union test {
            __m256 vec; // a data field, maybe a register, maybe not
            float array[8];
            test(__m256 vec)
                    : vec(vec) {}
        };

        test u_value = value;
        std::cout << "[" << u_value.array[0] << "," << u_value.array[1] << "," << u_value.array[2] << "," << u_value.array[3]
                  << "," << u_value.array[4] << "," << u_value.array[5] << "," << u_value.array[6] << "," << u_value.array[7] << "]" << std::endl;
    }

#else

    template <typename T>
    static std::string debug_d(T) {
        return "";
    }

    template <typename T>
    static std::string debug_s(T) {
        return "";
    }

#endif

    ETL_INLINE_VEC_VOID storeu(float* memory, __m256 value) {
        _mm256_storeu_ps(memory, value);
    }

    ETL_INLINE_VEC_VOID storeu(double* memory, __m256d value) {
        _mm256_storeu_pd(memory, value);
    }

    ETL_INLINE_VEC_VOID storeu(std::complex<float>* memory, __m256 value) {
        _mm256_storeu_ps(reinterpret_cast<float*>(memory), value);
    }

    ETL_INLINE_VEC_VOID storeu(std::complex<double>* memory, __m256d value) {
        _mm256_storeu_pd(reinterpret_cast<double*>(memory), value);
    }

    ETL_INLINE_VEC_VOID storeu(etl::complex<float>* memory, __m256 value) {
        _mm256_storeu_ps(reinterpret_cast<float*>(memory), value);
    }

    ETL_INLINE_VEC_VOID storeu(etl::complex<double>* memory, __m256d value) {
        _mm256_storeu_pd(reinterpret_cast<double*>(memory), value);
    }

    ETL_INLINE_VEC_VOID stream(float* memory, __m256 value) {
        _mm256_stream_ps(memory, value);
    }

    ETL_INLINE_VEC_VOID stream(double* memory, __m256d value) {
        _mm256_stream_pd(memory, value);
    }

    ETL_INLINE_VEC_VOID stream(std::complex<float>* memory, __m256 value) {
        _mm256_stream_ps(reinterpret_cast<float*>(memory), value);
    }

    ETL_INLINE_VEC_VOID stream(std::complex<double>* memory, __m256d value) {
        _mm256_stream_pd(reinterpret_cast<double*>(memory), value);
    }

    ETL_INLINE_VEC_VOID stream(etl::complex<float>* memory, __m256 value) {
        _mm256_stream_ps(reinterpret_cast<float*>(memory), value);
    }

    ETL_INLINE_VEC_VOID stream(etl::complex<double>* memory, __m256d value) {
        _mm256_stream_pd(reinterpret_cast<double*>(memory), value);
    }

    ETL_INLINE_VEC_VOID store(float* memory, __m256 value) {
        _mm256_store_ps(memory, value);
    }

    ETL_INLINE_VEC_VOID store(double* memory, __m256d value) {
        _mm256_store_pd(memory, value);
    }

    ETL_INLINE_VEC_VOID store(std::complex<float>* memory, __m256 value) {
        _mm256_store_ps(reinterpret_cast<float*>(memory), value);
    }

    ETL_INLINE_VEC_VOID store(std::complex<double>* memory, __m256d value) {
        _mm256_store_pd(reinterpret_cast<double*>(memory), value);
    }

    ETL_INLINE_VEC_VOID store(etl::complex<float>* memory, __m256 value) {
        _mm256_store_ps(reinterpret_cast<float*>(memory), value);
    }

    ETL_INLINE_VEC_VOID store(etl::complex<double>* memory, __m256d value) {
        _mm256_store_pd(reinterpret_cast<double*>(memory), value);
    }

    ETL_INLINE_VEC_256 load(const float* memory) {
        return _mm256_load_ps(memory);
    }

    ETL_INLINE_VEC_256D load(const double* memory) {
        return _mm256_load_pd(memory);
    }

    ETL_INLINE_VEC_256 load(const std::complex<float>* memory) {
        return _mm256_load_ps(reinterpret_cast<const float*>(memory));
    }

    ETL_INLINE_VEC_256D load(const std::complex<double>* memory) {
        return _mm256_load_pd(reinterpret_cast<const double*>(memory));
    }

    ETL_INLINE_VEC_256 load(const etl::complex<float>* memory) {
        return _mm256_load_ps(reinterpret_cast<const float*>(memory));
    }

    ETL_INLINE_VEC_256D load(const etl::complex<double>* memory) {
        return _mm256_load_pd(reinterpret_cast<const double*>(memory));
    }

    ETL_INLINE_VEC_256 loadu(const float* memory) {
        return _mm256_loadu_ps(memory);
    }

    ETL_INLINE_VEC_256D loadu(const double* memory) {
        return _mm256_loadu_pd(memory);
    }

    ETL_INLINE_VEC_256 loadu(const std::complex<float>* memory) {
        return _mm256_loadu_ps(reinterpret_cast<const float*>(memory));
    }

    ETL_INLINE_VEC_256D loadu(const std::complex<double>* memory) {
        return _mm256_loadu_pd(reinterpret_cast<const double*>(memory));
    }

    ETL_INLINE_VEC_256 loadu(const etl::complex<float>* memory) {
        return _mm256_loadu_ps(reinterpret_cast<const float*>(memory));
    }

    ETL_INLINE_VEC_256D loadu(const etl::complex<double>* memory) {
        return _mm256_loadu_pd(reinterpret_cast<const double*>(memory));
    }

    ETL_INLINE_VEC_256D set(double value) {
        return _mm256_set1_pd(value);
    }

    ETL_INLINE_VEC_256 set(float value) {
        return _mm256_set1_ps(value);
    }

    ETL_INLINE_VEC_256D add(__m256d lhs, __m256d rhs) {
        return _mm256_add_pd(lhs, rhs);
    }

    ETL_INLINE_VEC_256D sub(__m256d lhs, __m256d rhs) {
        return _mm256_sub_pd(lhs, rhs);
    }

    ETL_INLINE_VEC_256D sqrt(__m256d x) {
        return _mm256_sqrt_pd(x);
    }

    ETL_INLINE_VEC_256D minus(__m256d x) {
        return _mm256_xor_pd(x, _mm256_set1_pd(-0.f));
    }

    ETL_INLINE_VEC_256 add(__m256 lhs, __m256 rhs) {
        return _mm256_add_ps(lhs, rhs);
    }

    ETL_INLINE_VEC_256 sub(__m256 lhs, __m256 rhs) {
        return _mm256_sub_ps(lhs, rhs);
    }

    ETL_INLINE_VEC_256 sqrt(__m256 lhs) {
        return _mm256_sqrt_ps(lhs);
    }

    ETL_INLINE_VEC_256 minus(__m256 x) {
        return _mm256_xor_ps(x, _mm256_set1_ps(-0.f));
    }

    template <bool Complex = false>
    ETL_TMP_INLINE(__m256) mul(__m256 lhs, __m256 rhs) {
        return _mm256_mul_ps(lhs, rhs);
    }

    template <bool Complex = false>
    ETL_TMP_INLINE(__m256d) mul(__m256d lhs, __m256d rhs) {
        return _mm256_mul_pd(lhs, rhs);
    }

    template <bool Complex = false>
    ETL_TMP_INLINE(__m256) div(__m256 lhs, __m256 rhs) {
        return _mm256_div_ps(lhs, rhs);
    }

    template <bool Complex = false>
    ETL_TMP_INLINE(__m256d) div(__m256d lhs, __m256d rhs) {
        return _mm256_div_pd(lhs, rhs);
    }

    ETL_INLINE_VEC_256 cos(__m256 x) {
        return etl::cos256_ps(x);
    }

    ETL_INLINE_VEC_256 sin(__m256 x) {
        return etl::sin256_ps(x);
    }

#ifndef __INTEL_COMPILER

    //Exponential

    ETL_INLINE_VEC_256 exp(__m256 x) {
        return etl::exp256_ps(x);
    }

    ETL_INLINE_VEC_256 log(__m256 x) {
        return etl::log256_ps(x);
    }

#else //__INTEL_COMPILER

    //Exponential

    ETL_INLINE_VEC_256D exp(__m256d x) {
        return _mm256_exp_pd(x);
    }

    ETL_INLINE_VEC_256 exp(__m256 x) {
        return _mm256_exp_ps(x);
    }

    //Logarithm

    ETL_INLINE_VEC_256D log(__m256d x) {
        return _mm256_log_pd(x);
    }

    ETL_INLINE_VEC_256 log(__m256 x) {
        return _mm256_log_ps(x);
    }

    //Min

    ETL_INLINE_VEC_256D min(__m256d lhs, __m256d rhs) {
        return _mm256_min_pd(lhs, rhs);
    }

    ETL_INLINE_VEC_256 min(__m256 lhs, __m256 rhs) {
        return _mm256_min_ps(lhs, rhs);
    }

    //Max

    ETL_INLINE_VEC_256D max(__m256d lhs, __m256d rhs) {
        return _mm256_max_pd(lhs, rhs);
    }

    ETL_INLINE_VEC_256 max(__m256 lhs, __m256 rhs) {
        return _mm256_max_ps(lhs, rhs);
    }

#endif //__INTEL_COMPILER
};

template <>
ETL_OUT_VEC_256 avx_vec::mul<true>(__m256 lhs, __m256 rhs) {
    //lhs = [x1.real, x1.img, x2.real, x2.img, ...]
    //rhs = [y1.real, y1.img, y2.real, y2.img, ...]

    //ymm1 = [y1.real, y1.real, y2.real, y2.real, ...]
    __m256 ymm1 = _mm256_moveldup_ps(rhs);

    //ymm2 = [x1.img, x1.real, x2.img, x2.real]
    __m256 ymm2 = _mm256_permute_ps(lhs, 0b10110001);

    //ymm3 = [y1.imag, y1.imag, y2.imag, y2.imag]
    __m256 ymm3 = _mm256_movehdup_ps(rhs);

    //ymm4 = ymm2 * ymm3
    __m256 ymm4 = _mm256_mul_ps(ymm2, ymm3);

//result = [(lhs * ymm1) -+ ymm4];

#ifdef __FMA__
    return _mm256_fmaddsub_ps(lhs, ymm1, ymm4);
#elif defined(__FMA4__)
    return _mm256_maddsub_ps(lhs, ymm1, ymm4);
#else
    __m256 tmp = _mm256_mul_ps(lhs, ymm1);
    return _mm256_addsub_ps(tmp, ymm4);
#endif
}

template <>
ETL_OUT_VEC_256D avx_vec::mul<true>(__m256d lhs, __m256d rhs) {
    //lhs = [x1.real, x1.img, x2.real, x2.img]
    //rhs = [y1.real, y1.img, y2.real, y2.img]

    //ymm1 = [y1.real, y1.real, y2.real, y2.real]
    __m256d ymm1 = _mm256_movedup_pd(rhs);

    //ymm2 = [x1.img, x1.real, x2.img, x2.real]
    __m256d ymm2 = _mm256_permute_pd(lhs, 0b0101);

    //ymm3 = [y1.imag, y1.imag, y2.imag, y2.imag]
    __m256d ymm3 = _mm256_permute_pd(rhs, 0b1111);

    //ymm4 = ymm2 * ymm3
    __m256d ymm4 = _mm256_mul_pd(ymm2, ymm3);

//result = [(lhs * ymm1) -+ ymm4];

#ifdef __FMA__
    return _mm256_fmaddsub_pd(lhs, ymm1, ymm4);
#elif defined(__FMA4__)
    return _mm256_maddsub_pd(lhs, ymm1, ymm4);
#else
    __m256d tmp = _mm256_mul_pd(lhs, ymm1);
    return _mm256_addsub_pd(tmp, ymm4);
#endif
}

template <>
ETL_OUT_VEC_256 avx_vec::div<true>(__m256 lhs, __m256 rhs) {
    //lhs = [x1.real, x1.img, x2.real, x2.img ...]
    //rhs = [y1.real, y1.img, y2.real, y2.img ...]

    //ymm0 = [y1.real, y1.real, y2.real, y2.real, ...]
    __m256 ymm0 = _mm256_moveldup_ps(rhs);

    //ymm1 = [y1.imag, y1.imag, y2.imag, y2.imag]
    __m256 ymm1 = _mm256_movehdup_ps(rhs);

    //ymm2 = [x1.img, x1.real, x2.img, x2.real]
    __m256 ymm2 = _mm256_permute_ps(lhs, 0b10110001);

    //ymm4 = [x.img * y.img, x.real * y.img]
    __m256 ymm4 = _mm256_mul_ps(ymm2, ymm1);

//ymm5 = subadd((lhs * ymm0), ymm4)

#ifdef __FMA__
    __m256 ymm5 = _mm256_fmsubadd_ps(lhs, ymm0, ymm4);
#else
    __m256 t1    = _mm256_mul_ps(lhs, ymm0);
    __m256 t2    = _mm256_sub_ps(_mm256_set1_ps(0.0), ymm4);
    __m256 ymm5  = _mm256_addsub_ps(t1, t2);
#endif

    //ymm3 = [y.imag^2, y.imag^2]
    __m256 ymm3 = _mm256_mul_ps(ymm1, ymm1);

//ymm0 = (ymm0 * ymm0 + ymm3)

#ifdef __FMA__
    ymm0 = _mm256_fmadd_ps(ymm0, ymm0, ymm3);
#else
    __m256 t3    = _mm256_mul_ps(ymm0, ymm0);
    ymm0         = _mm256_add_ps(t3, ymm3);
#endif

    //result = ymm5 / ymm0
    return _mm256_div_ps(ymm5, ymm0);
}

template <>
ETL_OUT_VEC_256D avx_vec::div<true>(__m256d lhs, __m256d rhs) {
    //lhs = [x1.real, x1.img, x2.real, x2.img]
    //rhs = [y1.real, y1.img, y2.real, y2.img]

    //ymm0 = [y1.real, y1.real, y2.real, y2.real]
    __m256d ymm0 = _mm256_movedup_pd(rhs);

    //ymm1 = [y1.imag, y1.imag, y2.imag, y2.imag]
    __m256d ymm1 = _mm256_permute_pd(rhs, 0b1111);

    //ymm2 = [x1.img, x1.real, x2.img, x2.real]
    __m256d ymm2 = _mm256_permute_pd(lhs, 0b0101);

    //ymm4 = [x.img * y.img, x.real * y.img]
    __m256d ymm4 = _mm256_mul_pd(ymm2, ymm1);

//ymm5 = subadd((lhs * ymm0), ymm4)

#ifdef __FMA__
    __m256d ymm5 = _mm256_fmsubadd_pd(lhs, ymm0, ymm4);
#else
    __m256d t1   = _mm256_mul_pd(lhs, ymm0);
    __m256d t2   = _mm256_sub_pd(_mm256_set1_pd(0.0), ymm4);
    __m256d ymm5 = _mm256_addsub_pd(t1, t2);
#endif

    //ymm3 = [y.imag^2, y.imag^2]
    __m256d ymm3 = _mm256_mul_pd(ymm1, ymm1);

//ymm0 = (ymm0 * ymm0 + ymm3)

#ifdef __FMA__
    ymm0 = _mm256_fmadd_pd(ymm0, ymm0, ymm3);
#else
    __m256d t3   = _mm256_mul_pd(ymm0, ymm0);
    ymm0         = _mm256_add_pd(t3, ymm3);
#endif

    //result = ymm5 / ymm0
    return _mm256_div_pd(ymm5, ymm0);
}

} //end of namespace etl

#endif //__AVX__
