/* 
PrimesBench/prime_seq.hpp by Chris 
21.01.2022 
*/

#ifndef PRIME_SEQ
#define PRIME_SEQ

#include "../prime_utils.hpp"

template <class T, auto ...Ns>
constexpr auto get_init_primes()
{
    constexpr auto Primorial = (Ns * ...);
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

    std::array<T, size> primes{};

    std::size_t idx = 0;
    for (std::size_t i = 2; i < Primorial; ++i)
    {
        if (is_prime_naive(i))
        {
            primes[idx] = i;
            ++idx;
        }
    }
    return primes;
}

template<class T, auto...Ns>
std::vector<T> find_primes_seq(T limit)
{
    auto offset_arr = get_offset_array<Ns...>();
    auto primorial = (Ns * ...);
    static constexpr auto init_primes = get_init_primes<T, Ns...>();
    std::vector<T> primes{init_primes.begin(), std::find_if(init_primes.begin(), init_primes.end(), [&](auto num){return num > limit;})};   //assuming offset array is all primes which holds for max(Ns) < 7
    auto is_prime = [&](const auto num)
    {
        for (const auto prime : primes)
        {
            if (num % prime == 0)
            {
                return false;
            }
            if (prime > std::sqrt(num))
            {
                return true;
            }
        }
        return true;    // Should be unreachable
    };
    for (T i = primorial; ; i += primorial)
    {
        for (const auto offset : offset_arr)
        {
            auto num = i + offset;
            if (num >= limit)
            {
                return primes;
            }
            if (is_prime(num))
            {
                primes.push_back(num);
            }
        }
    }
    primes.insert(primes.begin(), {Ns...});
}

#endif