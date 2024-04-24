/*
PrimesBench/sieve_of_euler.hpp by Chris
22.01.2022
*/


#ifndef SIEVE_OF_EULER_HPP
#define SIEVE_OF_EULER_HPP

#include "../prime_utils.hpp"



template<class T>
std::vector<T> sieve_of_euler(T limit)
{
    std::vector<std::uint8_t> is_prime(limit, false);
    is_prime[2] = true;
    for (T idx = 3; idx < limit; idx += 2) 
    {
        is_prime[idx] = true;
    }
    for (T p = 3; p < limit; p += 2)
    {
        if (is_prime[p])
        {
            T max_q = limit/p;
            if(max_q % 2 == 0) --max_q;
            for (T q = max_q; q >= p; q -= 2)
            {
                if (is_prime[q])
                {
                    is_prime[p * q] = false;
                }
            }
        }
    }
    std::vector<T> out_vec{};
    for (T idx = 2; idx < limit; ++idx)
    {
        if (is_prime[idx])
        {
            out_vec.push_back(idx);
        }
    }
    return out_vec;
}




template<class T>
std::vector<T> sieve_of_euler_skip2(T limit)
{
    auto limit_idx = num_to_idx2(limit);
    std::vector<std::uint8_t> is_prime(limit_idx, true);
    for (T p = 0; p < limit_idx; ++p)
    {
        if (is_prime[p])
        {
            auto p_num = idx_to_num2(p);
            T max_q = limit / p_num;
            if(max_q % 2 == 0) --max_q;
            for (T q = max_q; q >= p_num; q -= 2)
            {
                if (is_prime[num_to_idx2(q)])
                {
                    is_prime[num_to_idx2(p_num * q)] = false;
                }
            }
        }
    }
    std::vector<T> out_vec{2};
    for (T idx = 0; idx < limit_idx; ++idx)
    {
        if (is_prime[idx])
        {
            out_vec.push_back(idx_to_num2(idx));
        }
    }
    return out_vec;
}



template<class T, auto...Ps>
std::vector<T> sieve_of_euler_skip_n(T limit)
{
    limit = round_up_to_nearest_offset<Ps...>(limit);
    auto limit_idx = num_to_idx<Ps...>(limit);
    std::vector<std::uint8_t> is_prime(limit_idx, true);
    for (T p = 0; p < limit_idx; ++p)
    {
        if (is_prime[p])
        {
            auto p_num = idx_to_num<Ps...>(p);
            T max_q = limit / p_num;
            max_q = round_down_to_nearest_offset<Ps...>(max_q);
            for (T q = max_q; q >= p_num; q = idx_to_num<Ps...>(num_to_idx<Ps...>(q) - 1))
            {
                if (is_prime[num_to_idx<Ps...>(q)])
                {
                    is_prime[num_to_idx<Ps...>(p_num * q)] = false;
                }
            }
        }
    }
    std::vector<T> out_vec{Ps...};
    for (T idx = 0; idx < limit_idx; ++idx)
    {
        if (is_prime[idx])
        {
            out_vec.push_back(idx_to_num<Ps...>(idx));
        }
    }
    return out_vec;
}




#endif