/*
PrimesBench/prime_wiki.hpp by Chris
22.01.2022
*/

#ifndef SIEVE_OF_AKTIN_HPP
#define SIEVE_OF_AKTIN_HPP
#include "../prime_utils.hpp"

template <class T>
std::vector<T> sieve_of_aktin(T limit)
{

    // Initialise the sieve array with false values
    std::vector<std::uint8_t> sieve(limit, false);

    /* Mark sieve[n] is true if one
       of the following is true:
    a) n = (4*x*x)+(y*y) has odd number of
       solutions, i.e., there exist
       odd number of distinct pairs (x, y)
       that satisfy the equation and
        n % 12 = 1 or n % 12 = 5.
    b) n = (3*x*x)+(y*y) has odd number of
       solutions and n % 12 = 7
    c) n = (3*x*x)-(y*y) has odd number of
       solutions, x > y and n % 12 = 11 */
    for (T x = 1; x * x < limit; x++)
    {
        for (T y = 1; y * y < limit; y++)
        {

            // Main part of Sieve of Atkin
            T n = (4 * x * x) + (y * y);
            if (n <= limit && (n % 12 == 1 || n % 12 == 5))
            {
                sieve[n] ^= true;
            }

            n = (3 * x * x) + (y * y);
            if (n <= limit && n % 12 == 7)
            {
                sieve[n] ^= true;
            }

            n = (3 * x * x) - (y * y);
            if (x > y && n <= limit && n % 12 == 11)
            {
                sieve[n] ^= true;
            }
        }
    }

    // Mark all multiples of squares as non-prime
    for (T r = 5; r * r < limit; r++)
    {
        if (sieve[r])
        {
            for (T i = r * r; i < limit; i += r * r)
            {
                sieve[i] = false;
            }
        }
    }
    std::vector<T> primes{2, 3};
    // Print primes using sieve[]
    for (T a = 5; a < limit; a++)
    {
        if (sieve[a])
        {
            primes.push_back(a);
        }
    }
    return primes;
}

template <class T>
std::vector<T> sieve_of_aktin2(const T limit)
{

    // Initialise the sieve array with false values
    std::vector<std::uint8_t> sieve(limit, false);

    /* Mark sieve[n] is true if one
       of the following is true:
    a) n = (4*x*x)+(y*y) has odd number of
       solutions, i.e., there exist
       odd number of distinct pairs (x, y)
       that satisfy the equation and
        n % 12 = 1 or n % 12 = 5.
    b) n = (3*x*x)+(y*y) has odd number of
       solutions and n % 12 = 7
    c) n = (3*x*x)-(y*y) has odd number of
       solutions, x > y and n % 12 = 11 */
    const auto root = static_cast<T>(std::sqrt(limit)) + 1;
    for (T x = 1; x < root; x++)
    {
        for (T y = 1; y < root; y++)
        {

            // Main part of Sieve of Atkin
            T n = (4 * x * x) + (y * y);
            if (n <= limit && (n % 12 == 1 || n % 12 == 5))
            {
                sieve[n] ^= true;
            }

            n = (3 * x * x) + (y * y);
            if (n <= limit && n % 12 == 7)
            {
                sieve[n] ^= true;
            }

            n = (3 * x * x) - (y * y);
            if (x > y && n <= limit && n % 12 == 11)
            {
                sieve[n] ^= true;
            }
        }
    }

    // Mark all multiples of squares as non-prime
    for (T r = 5; r * r < limit; r++)
    {
        if (sieve[r])
        {
            for (T i = r * r; i < limit; i += r * r)
            {
                sieve[i] = false;
            }
        }
    }
    std::vector<T> primes{2, 3};
    // Print primes using sieve[]
    for (T a = 5; a < limit; a++)
    {
        if (sieve[a])
        {
            primes.push_back(a);
        }
    }
    return primes;
}

#endif