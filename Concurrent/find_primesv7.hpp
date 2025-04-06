//
// Created by chris on 4/6/25.
//

#ifndef FIND_PRIMESV7_HPP
#define FIND_PRIMESV7_HPP
#include "../prime_utils.hpp"
#include <chrono>
#include <memory>
#include <cstdlib>
#include <barrier>

using u32 = std::uint32_t;


inline std::vector<std::uint32_t> primesv7(std::uint32_t limit)
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


#pragma omp parallel for schedule(static) num_threads(16)
        for (u32 q_idx = 1; q_idx <= max_q_idx; ++q_idx)
        {
            is_prime[3 * q_idx + 3] = false; // same as lower loop but p_idx = 0
        }
        auto sqr_index = num_to_idx2(p_num * p_num);
        is_prime[sqr_index] = false;
    }


#pragma omp parallel for schedule(static, 1) num_threads(8)
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



inline std::vector<std::uint32_t> primesv7_instrumented(std::uint32_t limit)
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
    std::cout << "Initializing Data: " << std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() <<
            '\n';
    start = now;
    // p_idx would be 0 so we would underflow so we special case for p_num == 3
    {
        constexpr u32 p_num = 3u;

        u32 max_q = limit / p_num;
        const u32 max_q_idx = num_to_idx2(max_q);

#pragma omp parallel for schedule(static) num_threads(16)
        for (u32 q_idx = 1; q_idx <= max_q_idx; ++q_idx)
        {
            is_prime[3 * q_idx + 3] = false; // same as lower loop but p_idx = 0
        }
        auto sqr_index = num_to_idx2(p_num * p_num);
        is_prime[sqr_index] = false;
    }

    now = std::chrono::steady_clock::now();
    std::cout << "Eliminating 3s: " << std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() <<
            '\n';
    start = now;



/*#pragma omp parallel for schedule(static, 1) num_threads(8)
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
    }*/

    std::vector<std::jthread> threads(7);
    std::atomic<u32> p_idx = 1;
    auto thread_f = [&]()
    {
        u32 my_p_idx = p_idx.fetch_add(1, std::memory_order::relaxed);
        while (my_p_idx < limit_sqrt_idx)
        {
            if (is_prime[my_p_idx])
            {
                const auto p_num = my_p_idx * 2 + 3;
                u32 max_q = limit / p_num;
                const u32 max_q_idx = num_to_idx2(max_q);

                for (u32 q_idx = max_q_idx; q_idx >= my_p_idx; --q_idx)
                {
                    if (is_prime[q_idx])
                    {
                        // is_prime[num_to_idx2(p_num * idx_to_num2(q_idx))] = false; equivalent to
                        is_prime[2 * my_p_idx * q_idx + 3 * (my_p_idx + q_idx) + 3] = false;
                    }
                }
            }
            my_p_idx = p_idx.fetch_add(1, std::memory_order::acq_rel);
        }
    };
    for (auto& t : threads)
    {
        t = std::jthread{thread_f};
    }
    thread_f();

    now = std::chrono::steady_clock::now();
    std::cout << "Other Primes: " << std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() << '\n';
    start = now;



    struct alignas(64) AlignedU32
    {
        u32 data[8];
    };

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
    return out_vec;
}


#endif //FIND_PRIMESV7_HPP
