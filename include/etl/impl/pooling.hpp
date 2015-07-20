//=======================================================================
// Copyright (c) 2014-2015 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#pragma once

#include <algorithm>

namespace etl {

namespace impl {

template<typename A, typename M>
struct max_pool_2d {
    template<std::size_t C1, std::size_t C2>
    static void apply(A&& sub, M& m){
        const auto o1 = etl::dim<0>(sub) / C1;
        const auto o2 = etl::dim<0>(sub) / C2;

        for(std::size_t j = 0; j < o1; ++j){
            for(std::size_t k = 0; k < o2; ++k){
                auto max = sub(j * C1, k * C2);

                for(std::size_t jj = 0; jj < C1; ++jj){
                    for(std::size_t kk = 0; kk < C2; ++kk){
                        max = std::max(max, sub(j * C1 + jj, k * C2 + kk));
                    }
                }

                m(j,k) = max;
            }
        }
    }
};

template<typename A, typename M>
struct avg_pool_2d {
    template<std::size_t C1, std::size_t C2>
    static void apply(A&& sub, M& m){
        const auto o1 = etl::dim<0>(sub) / C1;
        const auto o2 = etl::dim<0>(sub) / C2;

        for(std::size_t j = 0; j < o1; ++j){
            for(std::size_t k = 0; k < o2; ++k){
                value_t<A> avg = 0;

                for(std::size_t jj = 0; jj < C1; ++jj){
                    for(std::size_t kk = 0; kk < C2; ++kk){
                        avg += sub(j * C1 + jj, k * C2 + kk);
                    }
                }

                m(j,k) = avg / (C1 * C2);
            }
        }
    }
};

} //end of namespace impl

} //end of namespace etl
