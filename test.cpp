#include "Sequential/find_primesv6.hpp"
#include "Sequential/prime_seq.hpp"
#include "Sequential/sieve_of_aktin.hpp"
#include "Sequential/sieve_of_sundaram.hpp"
#include "Sequential/sieve_of_eratosthenes.hpp"
#include "Sequential/sieve_of_euler.hpp"


#include <algorithm>
#include <ranges>
#include <print>

#include "Sequential/find_primesv5.hpp"
#include "Concurrent/find_primesv7.hpp"
#include "Concurrent/find_primesv8.hpp"

namespace v = std::views;
namespace r = std::ranges;

std::vector<std::tuple<std::uint32_t, std::uint32_t>> get_zipped(std::uint32_t limit)
{
    auto p6 = primesv8(limit);
    auto p5 = primesv5(limit);
    return v::zip(p6, p5) | r::to<std::vector>();
}


void print(const std::vector<std::tuple<std::uint32_t, std::uint32_t>>& primes)
{
    for (auto [p1, p2] : primes)
    {
        std::cout << p1 << '\t' << p2 << '\n';
    }

}


void print(const std::vector<std::uint32_t>& primes)
{
    for (auto p1 : primes)
    {
        std::cout << p1 << '\n';
    }

}

void test(std::uint32_t limit)
{
    auto primes = get_zipped(limit);
    auto equal = r::all_of(primes, [](auto p)
    {
        return std::apply(std::equal_to<>{}, p);
    });
    if (not equal)
    {
        std::cout << "Error with " << limit << '\n';
    } else
    {
        std::cout << "All equal for " << limit << '\n';
    }
}

void test()
{
    for (std::uint32_t limit = 32; limit <= 1 << 30; limit <<= 1)
    {
        test(limit);
    }
}

int main()
{

    std::cout << std::thread::hardware_concurrency() << '\n';

}