#include "Concurrent/find_primesv5.hpp"
#include "Sequential/prime_seq.hpp"
#include "Sequential/sieve_of_aktin.hpp"
#include "Sequential/sieve_of_sundaram.hpp"
#include "Sequential/sieve_of_eratosthenes.hpp"
#include "Sequential/sieve_of_euler.hpp"


#include <algorithm>

int main()
{
    auto primes = primesv5(1'000'000);
    auto soe = sieve_of_eratosthenes<std::uint32_t>(1'000'000);
    std::cout << primes.size() << '\t' << soe.size() << "\n\n";
    for (std::size_t i = 0; i < std::min(primes.size(), soe.size()); ++i)
    {
        std::cout << soe[i] << " " << primes[i] << '\n';
    }




}