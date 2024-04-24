/* 
PrimesBench/sieve_of_eratosthenes.hpp by Chris 
27.01.2022 
*/

#ifndef SIEVE_OF_ERATOSTHENES_HPP
#define SIEVE_OF_ERATOSTHENES_HPP

#include "../prime_utils.hpp"

template<class T>
std::vector<T> sieve_of_eratosthenes(const T limit)
{
    std::vector<std::uint8_t> sieve(limit, true);
    const T sqrt = std::sqrt(limit);
    for (T idx = 2; idx < sqrt + 1; ++idx)
    {
        if (sieve[idx])
        {
            for (T not_prime = idx*idx; not_prime < limit; not_prime += idx)
            {
                sieve[not_prime] = false;
            }
        }
    }
    std::vector<T> primes{};
    for (T idx = 2; idx < limit; ++idx)
    {
        if (sieve[idx])
        {
            primes.push_back(idx);
        }
    }
    return primes;
}





// Numbers represented by sieve are 3, 5, 7, 9, 11, 13, ...
template<class T>
std::vector<T> sieve_of_eratosthenes_skip2(const T limit)
{
    const T index_limit = num_to_idx2(limit);
    std::vector<std::uint8_t> sieve(index_limit, true);
    const T sqrt_limit = std::sqrt(limit);  // the square root of upper limit as a number
    const T sqrt_limit_idx = num_to_idx2(sqrt_limit);    // the index of that number in the array
    for (T idx = 0; idx < sqrt_limit_idx + 1; ++idx)
    {
        // if 3 is prime
        if (sieve[idx])
        {

            auto num = idx_to_num2(idx);
            for (T not_prime = num_to_idx2(num * num); not_prime < index_limit; not_prime = num_to_idx2(idx_to_num2(not_prime) + 2 * num))
            {
                sieve[not_prime] = false;
            }
        }
    }
    std::vector<T> primes{2};
    for (T idx = 0; idx < index_limit; ++idx)
    {
        if (sieve[idx])
        {
            primes.push_back(idx_to_num2(idx));
        }
    }
    return primes;
}


#endif