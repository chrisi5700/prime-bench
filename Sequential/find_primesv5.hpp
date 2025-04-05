//
// Created by chris on 23.02.24.
//

#ifndef PRIMEBENCH_FIND_PRIMESV5_HPP
#define PRIMEBENCH_FIND_PRIMESV5_HPP

#include "../prime_utils.hpp"

inline std::vector<std::uint32_t> primesv5(std::uint32_t limit)
{
    using u32 = std::uint32_t;
    auto limit_idx = num_to_idx2(limit);
    std::vector<std::uint8_t> is_prime(limit_idx, true);



    for (u32 p_idx = 0; p_idx < limit_idx; ++p_idx)
    {
        if (is_prime[p_idx])
        {
            auto p_num = idx_to_num2(p_idx);
            u32 max_q = limit / p_num;
            if(max_q % 2 == 0) --max_q;
            u32 max_q_idx = num_to_idx2(max_q);
            for (u32 q_idx = max_q_idx; idx_to_num2(q_idx) >= p_num; --q_idx)
            {
                if (is_prime[q_idx])
                {
                    is_prime[num_to_idx2(p_num * idx_to_num2(q_idx))] = false;
                }
            }

        }
    }
    std::vector<u32> out_vec{2};
    out_vec.reserve(limit / std::log(limit));
    for (u32 idx = 0; idx < limit_idx; ++idx)
    {
        if (is_prime[idx])
        {
            out_vec.emplace_back(idx_to_num2(idx));
        }
    }
    return out_vec;
}

#endif // PRIMEBENCH_FIND_PRIMESV5_HPP
