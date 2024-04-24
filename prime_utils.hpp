/* 
PrimesBench/prime_utils.hpp by Chris 
20.01.2022 
*/

#ifndef PRIME_UTILS_CONC_HPP
#define PRIME_UTILS_CONC_HPP
#include <thread>
#include <barrier>
#include <algorithm>
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
#include <ranges>

template <auto... Ns>
constexpr auto get_offset_length()
{
    auto primorial = (Ns * ...);
    auto not_divides = [](auto i, auto n)
    { return i % n != 0; };
    std::size_t count{};
    for (decltype(primorial) i = 0; i < primorial; ++i)
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
    for (decltype(primorial) i = 0; i < primorial; ++i)
    {
        if ((not_divides(i, Ns) && ...))
        {
            offsets[idx] = i;
            ++idx;
        }
    }
    return offsets;
}

auto num_to_idx2(auto num)
{
    return (num - 3) / 2;
}

auto idx_to_num2(auto idx)
{
    return idx * 2 + 3;
}


template<auto... Ps>
auto repeat_offsets(std::size_t idx)
{
    static constexpr auto array = get_offset_array<Ps...>();
    static constexpr auto primorial = (Ps * ...);
    auto div = idx / array.size();
    auto mod = idx % array.size();
    return primorial * div + array[mod];
}


std::size_t binary_search_idx(std::ranges::sized_range auto & range, auto elem)
{
    std::size_t left = 0;
    std::size_t right = range.size() - 1;
    while (left <= right)
    {
        std::size_t m = left + (right - left) / 2;
        if (range[m] == elem) return m;
        if (range[m] < elem) left = m + 1;
        else right = m - 1;
    }
    std::unreachable();
}

// Inverse to repeat_offsets
template<auto...Ps>
auto offsets_to_idx(auto offset)
{
    static constexpr auto array = get_offset_array<Ps...>();
    static constexpr auto primorial = (Ps * ...);
    auto div = offset / primorial;
    auto mod = offset % primorial;
    auto i = binary_search_idx(array, mod);
    return div * array.size() + i;

}


// If true then offset is definitely not prime if false it might be prime
template<auto...Ps>
auto definitely_not_prime(auto offset)
{
    using std::ranges::binary_search;
    static constexpr auto array = get_offset_array<Ps...>();
    static constexpr auto primorial = (Ps * ...);
    auto mod = offset % primorial;
    return not binary_search(array, mod);

}

template<auto...Ps>
auto round_up_to_nearest_offset(auto num)
{
    if (not definitely_not_prime<Ps...>(num)) return num;
    static constexpr auto array = get_offset_array<Ps...>();
    static constexpr auto primorial = (Ps * ...);
    auto mod = num % primorial;
    std::size_t i = 0;
    while (mod >= array[i]) ++i;

    return num + (array[i] - mod);
}

template<auto...Ps>
auto round_down_to_nearest_offset(auto num)
{
    if (not definitely_not_prime<Ps...>(num)) return num;
    static constexpr auto array = get_offset_array<Ps...>();
    static constexpr auto primorial = (Ps * ...);
    auto mod = num % primorial;
    std::size_t i = 0;
    while (mod > array[i]) ++i;
    if (i != 0)
    {
        return num - (mod - array[i-1]);
    }
    return num - 1;
}

template<auto...Ps>
auto idx_to_num(std::size_t idx)
{
    return repeat_offsets<Ps...>(idx+1);  // 1 is never prime so we can always skip it
}


template<auto...Ps>
auto num_to_idx(auto num)
{
    return offsets_to_idx<Ps...>(num) - 1;  // 1 is never prime so we can always skip it
}




#endif