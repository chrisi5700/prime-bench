#pragma once


#include "../prime_utils.hpp"

namespace rv = std::ranges;


template <class T, auto... Ns>
auto find_primesv2(T lim)
{
    static constexpr auto offsets = get_offset_array<Ns...>();
    constexpr auto primorial = (Ns * ...);
    std::vector<T> primes{};
    constexpr auto thread_count = offsets.size();
    for (std::size_t i = 1; i < thread_count; ++i)
    {
        /* if (offsets[i] > "last_elem of Ns²")
        {
            break;
        } */
        primes.push_back(offsets[i]);
    }
    std::array<std::vector<T>, thread_count> prime_qs;
    T current_limit = 0;
    auto flush_prime_qs = [&]()
    {
        std::size_t idx{0};
        while (rv::any_of(prime_qs, [&](const auto &vec)
                          { return idx < vec.size(); }))
        {
            for (std::size_t i = 0; i < thread_count; ++i)
            {
                if (idx < prime_qs[i].size())
                {
                    auto elem = prime_qs[i][idx];
                    if (elem != 0)
                    {
                        primes.push_back(elem);
                    }
                }
            }
            ++idx;
        }
        rv::for_each(prime_qs, [](auto &vec)
                     { vec.clear(); });
    };

    auto update_current_limit = [&]()
    {
        if (current_limit < lim)
        {
            auto latest_prime = primes.back();
            if (std::bit_width(latest_prime) * 2 > sizeof(T) * 8 || latest_prime * latest_prime > lim)
            {
                current_limit = lim;
            }
            else
            {
                current_limit = latest_prime * latest_prime;
            }
        }
    };

    auto is_prime = [&](const T num)
    {
        for (auto prime : primes)
        {
            if (num % prime == 0)
            {
                return false;
            }
            if (std::sqrt(num) < prime)
            {
                break;
            }
        }
        return true;
    };

    std::barrier sync_point{thread_count, [&]()
                            {
                                flush_prime_qs();
                                update_current_limit();
                            }};

    auto find_primes_thread = [&](auto offset, auto idx)
    {
        for (T i = primorial + offset; i < lim; i += primorial)
        {
            if (i > current_limit)
            {
                sync_point.arrive_and_wait();
            }
            prime_qs[idx].push_back(i * is_prime(i));
        }
        sync_point.arrive_and_drop();
    };

    std::array<std::jthread, thread_count> threads{};
    for (std::size_t i = 0; i < thread_count; ++i)
    {
        threads[i] = std::jthread(find_primes_thread, offsets[i], i);
    }
    return primes;
}