/*
PrimesBench/sieve_of_sundaram.hpp by Chris
22.01.2022
*/

#ifndef SIEVE_OF_SUNDARAM_HPP
#define SIEVE_OF_SUNDARAM_HPP

#include "../prime_utils.hpp"

template <class T>
std::vector<T> sieve_of_sundaram(const T limit)
{
    T k = (limit - 2) / 2;
    T root = static_cast<T>(std::sqrt(limit));
    std::vector<std::uint8_t> sieve(k + 1, true);
    for (T i = 1; i < (root/2 + 1); ++i)
    {

        for (T j = i + i + 2 * i * i; j <= k; j += 2*i + 1)
        {
            sieve[j] = false;
        }
    }
    std::vector<T> primes{2};
    for (T i = 1; i < k + 1; ++i)
    {
        if (sieve[i])
        {
            primes.push_back(2 * i + 1);
        }
    }
    return primes;
}

template <class T>
std::vector<T> sieve_of_sundaram2(const T limit)
{
    const T k = (limit - 2) / 2;
    const T root = static_cast<T>(std::sqrt(limit));
    std::vector<std::uint8_t> sieve(k + 1, true);
    for (T i = 1; i < (root/2 + 1); ++i)
    {

        for (T j = i + i + 2 * i * i; j <= k; j += 2*i + 1)
        {
            sieve[j] = false;
        }
    }
    std::vector<T> primes{2};
    primes.reserve(limit/3 + 2);
    for (T i = 1; i < k + 1; ++i)
    {
        if (sieve[i])
        {
            primes.push_back(2 * i + 1);
        }
    }
    primes.shrink_to_fit();
    return primes;
}




#endif