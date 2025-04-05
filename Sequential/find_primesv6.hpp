//
// Created by chris on 23.02.24.
//

#ifndef PRIMEBENCH_FIND_PRIMESV6_HPP
#define PRIMEBENCH_FIND_PRIMESV6_HPP


#include <parallel/algorithm>
#include "../prime_utils.hpp"

inline std::vector<std::uint32_t> primesv6(std::uint32_t limit)
{
    using u32 = std::uint32_t;
    limit += limit % 2 + 1;

    const auto limit_idx = num_to_idx2(limit); // limit should be odd
    std::vector<std::uint8_t> is_prime(limit_idx, true);


    for (u32 p_idx = 0; p_idx < limit_idx; ++p_idx)
    {
        if (is_prime[p_idx])
        {
            const auto p_num = p_idx * 2 +3;
            u32 max_q = limit / p_num;
            max_q += max_q % 2;
                    // Make odd
            if (max_q <= 2) continue;
            const u32 max_q_idx = num_to_idx2(max_q);
            for (u32 q_idx = max_q_idx; q_idx > p_idx; --q_idx)
            {
                if (is_prime[q_idx])
                {
                    is_prime[2 * p_idx * q_idx + 3 * (p_idx + q_idx) + 3] = false;}
            }

        }
    }


    // Eliminate square numbers
    const u32 limit_sqrt = std::sqrt(limit) + 1;
    for (u32 sq = 3; sq < limit_sqrt; sq += 2)
    {
        is_prime[num_to_idx2(sq * sq)] = false;
    }



    std::vector<u32> out_vec{2};
    out_vec.reserve(limit / std::log(limit) * 1.1); // never reallocate

    for (u32 idx = 0; idx < limit_idx; ++idx)
    {
        if (is_prime[idx])
        {
            out_vec.emplace_back(idx_to_num2(idx));
        }
    }
    return out_vec;

}





#endif // PRIMEBENCH_FIND_PRIMESV6_HPP
