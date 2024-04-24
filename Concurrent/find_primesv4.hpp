//
// Created by chris on 22.02.24.
//

#ifndef PRIMEBENCH_FIND_PRIMESV4_HPP
#define PRIMEBENCH_FIND_PRIMESV4_HPP


#include "../prime_utils.hpp"
#include <chrono>

template<class T>
std::vector<T> primesv4(const T limit)
{
    static constexpr std::size_t thread_count = 8;
    std::vector<std::jthread> thread_pool;
    auto limit_idx = num_to_idx2(limit + limit % 2);
    std::vector<std::uint8_t> sieve(limit_idx, true);
    const T sqrt = std::sqrt(limit);
    const T sqrtsqrt = std::sqrt(sqrt);
    const T sqrt_idx = num_to_idx2(sqrt + 1);


    // First generate all the primes needed to generate up to the limit in a single thread
    for (T num = idx_to_num2(0); num < sqrtsqrt + 1; num += 2)
    {
        if (sieve[num_to_idx2(num)])
        {
            for (T not_prime = num * num; not_prime < sqrt; not_prime += 2 * num)
            {
                sieve[num_to_idx2(not_prime)] = false;
            }
        }
    }

    auto thread_func = [&](std::size_t id)
    {
        std::size_t prime_idx = 0;
        for (T idx = 0; idx < sqrt_idx; ++idx)
        {
            if (sieve[idx])
            {
                if (prime_idx % thread_count == id)
                {
                    auto num = idx_to_num2(idx);

                    for (T not_prime = num * num; not_prime < limit; not_prime += 2 * num)
                    {
                        sieve[num_to_idx2(not_prime)] = false;
                    }
                }
                prime_idx++;
            }
        }
    };



    for (std::size_t i = 0; i < thread_count; ++i)
    {
        thread_pool.emplace_back(thread_func, i);
    }

    for (auto& t : thread_pool)
    {
        t.join();
    }

    std::vector<T> primes{2};
    for (T idx = 0; idx < limit_idx; ++idx)
    {
        if (sieve[idx])
        {
            primes.push_back(idx_to_num2(idx));
        }
    }

    return primes;
}


#endif // PRIMEBENCH_FIND_PRIMESV4_HPP
