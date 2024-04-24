/*
PrimesBench/prime_conc.hpp by Chris
11.01.2022
*/

#ifndef PRIME_CONC
#define PRIME_CONC

#include <thread>
#include <barrier>
#include <vector>
#include <array>
#include <cmath>
#include <deque>
#include <iostream>
#include <algorithm>
#include <bit>
#include <atomic>
#include <mutex>
#include <shared_mutex>
#include <utility>

namespace rv = std::ranges;

template <auto... Ns>
constexpr auto get_offset_length()
{
    auto primorial = (Ns * ...);
    auto not_divides = [](auto i, auto n)
    { return i % n != 0; };
    std::size_t count{};
    for (std::size_t i = 0; i < primorial; ++i)
    {
        if ((not_divides(i, Ns) && ...))
        {
            ++count;
        }
    }
    return count;
}

template <auto... Ns>
constexpr auto get_offset_array()
{
    auto primorial = (Ns * ...);
    auto not_divides = [](auto i, auto n)
    { return i % n != 0; };
    constexpr auto size = get_offset_length<Ns...>();
    std::array<decltype(primorial), size> offsets{};
    auto idx = 0;
    for (std::size_t i = 0; i < primorial; ++i)
    {
        if ((not_divides(i, Ns) && ...))
        {
            offsets[idx] = i;
            ++idx;
        }
    }
    return offsets;
}

template <class T, auto... Ns>
auto find_primesv1(T lim)
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
    std::array<std::deque<T>, thread_count> prime_qs;
    T current_limit = 0;
    auto flush_prime_qs = [&]()
    {
        while (rv::any_of(prime_qs, [](const auto &q)
                          { return !q.empty(); }))
        {
            for (std::size_t i = 0; i < thread_count; ++i)
            {
                if (!prime_qs[i].empty())
                {
                    auto elem = prime_qs[i].front();
                    prime_qs[i].pop_front();
                    if (elem != 0)
                    {
                        primes.push_back(elem);
                    }
                }
            }
        }
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

/*
    V2 Improvements: Removed need for dequeus added vectors instead
*/

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

/*

    V3 Improvements: Unified vectors into a single q vector which is more cache friendly

*/

template <class T, auto... Ns>
auto find_primesv3(T lim)
{
    static constexpr auto offsets = get_offset_array<Ns...>();
    constexpr auto primorial = (Ns * ...);
    std::vector<T> primes{};
    constexpr auto thread_count = offsets.size();
    for (std::size_t i = 1; i < thread_count; ++i)
    {
        /* if (offsets[i] > std::max({(std::pow(Ns, 2), ...)}))
        {
            break;
        } */
        primes.push_back(offsets[i]);
    }
    std::vector<T> prime_q;
    T current_limit = std::min(lim, primes.back() * primes.back());
    T last_limit = 0;
    auto flush_prime_q = [&]()
    {
        for (const auto &elem : prime_q)
        {
            if (elem != 0)
            {
                primes.push_back(elem);
            }
        }
        // prime_q.clear();
    };

    auto update_current_limit = [&]()
    {
        last_limit = current_limit;
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

    auto resize_prime_q = [&]()
    {
        T lim_diff = current_limit - last_limit;
        T steps = std::ceil(lim_diff / static_cast<double>(primorial));
        prime_q = std::vector<T>(steps * thread_count);
        /*
            Split the prime calculation into steps steps and allocate a slot for each possible prime number per thread
        */
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
                                flush_prime_q();
                                update_current_limit();
                                resize_prime_q();
                            }};

    auto find_primes_thread = [&](auto offset, auto idx)
    {
        auto prime_q_idx = 0;
        for (T curr_num = offset + primorial; curr_num < lim; curr_num += primorial)
        {
            if (curr_num > current_limit)
            {
                sync_point.arrive_and_wait();
                prime_q_idx = 0;
            }
            if (is_prime(curr_num))
            {
                prime_q[thread_count * prime_q_idx + idx] = curr_num;
            }
            ++prime_q_idx;
        }
        sync_point.arrive_and_drop();
    };

    resize_prime_q();
    std::array<std::jthread, thread_count> threads{};
    for (std::size_t i = 0; i < thread_count; ++i)
    {
        threads[i] = std::jthread(find_primes_thread, offsets[i], i);
    }
    return primes;
}

/*

V4: Added possible optimizations to catch non primes faster

*/

template <auto Primorial>
constexpr auto get_small_prime_test()
{
    constexpr auto is_prime_naive = [](auto num)
    {
        for (std::size_t i = 2; i < num; ++i)
        {
            if (num % i == 0)
            {
                return false;
            }
        }
        return true;
    };

    constexpr auto size = [&]()
    {
        std::size_t _size = 0;
        for (std::size_t i = 2; i < Primorial; ++i)
        {
            if (is_prime_naive(i))
            {
                ++_size;
            }
        }
        return _size;
    }();

    std::array<decltype(Primorial), size> primes{};

    std::size_t idx = 0;
    for (std::size_t i = 2; i < Primorial; ++i)
    {
        if (is_prime_naive(i))
        {
            primes[idx] = i;
            ++idx;
        }
    }
    return [=](auto num)
    {
        for (auto p : primes)
        {
            if (num % p == 0)
            {
                return false;
            }
        }
        return true;
    };
}

template<auto Primorial>
constexpr auto get_largest_prime()
{
    constexpr auto is_prime = [](auto num)
    {
        for (std::size_t i = 2; i < num; ++i)
        {
            if (num % i == 0)
            {
                return false;
            }
        }
        return true;
    };
    decltype(Primorial) prime = 2u;
    for (std::size_t i = 3; i < Primorial; ++i)
    {
        if (is_prime(i))
        {
            prime = i;
        }
    }
    return prime;
}


template <class T, T... Ns>
auto find_primesv4(T lim)
{
    static constexpr auto offsets = get_offset_array<Ns...>();
    constexpr auto primorial = (Ns * ...);
    std::vector<T> primes{};
    constexpr auto thread_count = offsets.size();
    std::vector<T> prime_q;

    constexpr auto initial_lim = get_largest_prime<primorial>();
    T current_limit = std::min({lim, initial_lim * initial_lim});
    T last_limit = 0;

    constexpr static auto small_prime_test = get_small_prime_test<primorial>();

    auto flush_prime_q = [&]()
    {
        for (const auto &elem : prime_q)
        {
            if (elem != 0)
            {
                primes.push_back(elem);
            }
        }
    };

    auto update_current_limit = [&]()
    {
        last_limit = current_limit;
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

    auto resize_prime_q = [&]()
    {
        T lim_diff = current_limit - last_limit;
        T steps = std::ceil(lim_diff / static_cast<double>(primorial));
        prime_q = std::vector<T>(steps * thread_count);
        /*
            Split the prime calculation into steps steps and allocate a slot for each possible prime number per thread
        */
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
                                flush_prime_q();
                                update_current_limit();
                                resize_prime_q();
                            }};

    auto find_primes_thread = [&](auto offset, auto idx)
    {
        auto prime_q_idx = 0;
        for (T curr_num = offset + primorial; curr_num < lim; curr_num += primorial)
        {
            if (curr_num > current_limit)
            {
                sync_point.arrive_and_wait();
                prime_q_idx = 0;
            }
            if (small_prime_test(curr_num) && is_prime(curr_num))
            {
                prime_q[thread_count * prime_q_idx + idx] = curr_num;
            }
            ++prime_q_idx;
        }
        sync_point.arrive_and_drop();
    };

    resize_prime_q();
    std::array<std::jthread, thread_count> threads{};
    for (std::size_t i = 0; i < thread_count; ++i)
    {
        threads[i] = std::jthread(find_primes_thread, offsets[i], i);
    }
    return primes;
}

#endif