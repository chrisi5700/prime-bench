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
    limit += -1 + limit % 2; // if even sub one. Should not change the result since even numbers arent prime

    const auto limit_idx = num_to_idx2(limit); // limit should be odd
    const u32 limit_sqrt = std::sqrt(limit);
    const u32 limit_sqrt_idx = num_to_idx2(limit_sqrt + (1 + limit % 2));

    std::vector<std::uint8_t> is_prime(limit_idx, true);

    // p_idx would be 0 so we would underflow so we special case for p_num == 3
    {
        const auto p_num = 3;

        u32 max_q = limit / p_num;
        const u32 max_q_idx = num_to_idx2(max_q);


        for (u32 q_idx = max_q_idx; q_idx > 0; --q_idx)
        {
            if (is_prime[q_idx])
            {
                is_prime[3 * q_idx + 3] = false; // same as lower loop but p_idx = 0
            }
        }
        auto sqr_index = num_to_idx2(p_num * p_num);
        is_prime[sqr_index] = false;
    }

    for (u32 p_idx = 1; p_idx < limit_sqrt_idx; ++p_idx)
    {
        if (is_prime[p_idx])
        {
            const auto p_num = p_idx * 2 + 3;
            u32 max_q = limit / p_num;
            const u32 max_q_idx = num_to_idx2(max_q);


            for (u32 q_idx = max_q_idx; q_idx >= p_idx; --q_idx)
            {
                if (is_prime[q_idx])
                {

                    // is_prime[num_to_idx2(p_num * idx_to_num2(q_idx))] = false; equivalent to
                    is_prime[2 * p_idx * q_idx + 3 * (p_idx + q_idx) + 3] = false;
                }
            }
        }
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


inline std::vector<std::uint32_t> primesv6_instrumented(std::uint32_t limit)
{
    auto start = std::chrono::steady_clock::now();
    auto now = start;
    using u32 = std::uint32_t;
    limit += -1 + limit % 2; // if even sub one. Should not change the result since even numbers arent prime

    const auto limit_idx = num_to_idx2(limit); // limit should be odd
    const u32 limit_sqrt = std::sqrt(limit);
    const u32 limit_sqrt_idx = num_to_idx2(limit_sqrt + (1 + limit % 2));

    std::vector<std::uint8_t> is_prime(limit_idx, true);
    now = std::chrono::steady_clock::now();
    std::cout << "Initializing Data: " << std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() << '\n';
    start = now;

    // p_idx would be 0 so we would underflow so we special case for p_num == 3
    {
        const auto p_num = 3;

        u32 max_q = limit / p_num;
        const u32 max_q_idx = num_to_idx2(max_q);


        for (u32 q_idx = max_q_idx; q_idx > 0; --q_idx)
        {
            if (is_prime[q_idx])
            {
                is_prime[3 * q_idx + 3] = false; // same as lower loop but p_idx = 0
            }
        }
        auto sqr_index = num_to_idx2(p_num * p_num);
        is_prime[sqr_index] = false;
    }
    now = std::chrono::steady_clock::now();
    std::cout << "Eliminating 3s: " << std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() << '\n';
    start = now;

    for (u32 p_idx = 1; p_idx < limit_sqrt_idx; ++p_idx)
    {
        if (is_prime[p_idx])
        {
            const auto p_num = p_idx * 2 + 3;
            u32 max_q = limit / p_num;
            const u32 max_q_idx = num_to_idx2(max_q);


            for (u32 q_idx = max_q_idx; q_idx >= p_idx; --q_idx)
            {
                if (is_prime[q_idx])
                {

                    // is_prime[num_to_idx2(p_num * idx_to_num2(q_idx))] = false; equivalent to
                    is_prime[2 * p_idx * q_idx + 3 * (p_idx + q_idx) + 3] = false;
                }
            }
        }
    }

    now = std::chrono::steady_clock::now();
    std::cout << "Other Primes: " << std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() << '\n';
    start = now;


    std::vector<u32> out_vec{2};
    out_vec.reserve(limit / std::log(limit) * 1.1); // never reallocate

    for (u32 idx = 0; idx < limit_idx; ++idx)
    {
        if (is_prime[idx])
        {
            out_vec.emplace_back(idx_to_num2(idx));
        }
    }

    now = std::chrono::steady_clock::now();
    std::cout << "Writing Data: " << std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() << '\n';
    start = now;
    return out_vec;

}




#endif // PRIMEBENCH_FIND_PRIMESV6_HPP
