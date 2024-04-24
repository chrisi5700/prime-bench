#pragma once

#include "../prime_utils.hpp"


namespace rv = std::ranges;


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