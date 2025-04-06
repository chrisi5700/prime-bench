#include "Concurrent/find_primesv3.hpp"
#include "Concurrent/find_primesv2.hpp"
#include "Concurrent/find_primesv4.hpp"
#include "Sequential/find_primesv5.hpp"
#include "Sequential/find_primesv6.hpp"


#include "Sequential/prime_seq.hpp"
#include "Sequential/sieve_of_aktin.hpp"
#include "Sequential/sieve_of_sundaram.hpp"
#include "Sequential/sieve_of_eratosthenes.hpp"
#include "Sequential/sieve_of_euler.hpp"


#include <iostream>
#include <benchmark/benchmark.h>

#include "Concurrent/find_primesv7.hpp"
#include "Concurrent/find_primesv8.hpp"


void BM_Sieve(benchmark::State &state, auto sieve)
{
    std::size_t count = 0;
    for (auto _ : state)    // NOLINT Place holder
    {
        auto primes = sieve(state.range(0));
        count += primes.size();
    }
    state.SetItemsProcessed(count); //NOLINT Googlebench uses signed for clearly unsigned operations
}

void BM_Eratosthenes(benchmark::State &state)
{
    BM_Sieve(state, sieve_of_eratosthenes<std::uint32_t>);
}

void BM_EratosthenesSkip2(benchmark::State &state)
{
    BM_Sieve(state, sieve_of_eratosthenes_skip2<std::uint32_t>);
}

void BM_Euler(benchmark::State &state)
{
    BM_Sieve(state, sieve_of_euler<std::uint32_t>);
}

void BM_EulerSkip2(benchmark::State &state)
{
    BM_Sieve(state, sieve_of_euler_skip2<std::uint32_t>);
}

void BM_EulerSkip2TMP(benchmark::State &state)
{
    BM_Sieve(state, sieve_of_euler_skip_n<std::uint32_t, 2, 3>);
}

void BM_EulerSkip23(benchmark::State &state)
{
    BM_Sieve(state, sieve_of_euler_skip_n<std::uint32_t, 2, 3>);
}

void BM_EulerSkip235(benchmark::State &state)
{
    BM_Sieve(state, sieve_of_euler_skip_n<std::uint32_t, 2, 3, 5>);
}


void BM_Aktin(benchmark::State &state)
{
    BM_Sieve(state, sieve_of_aktin<std::uint32_t>);
}

void BM_Aktin2(benchmark::State &state)
{
    BM_Sieve(state, sieve_of_aktin2<std::uint32_t>);
}


void BM_Sundaram(benchmark::State &state)
{
    BM_Sieve(state, sieve_of_sundaram<std::uint32_t>);
}

void BM_PrimesV4(benchmark::State &state)
{
    BM_Sieve(state, primesv4<std::uint32_t>);
}

void BM_PrimesV5(benchmark::State &state)
{
    BM_Sieve(state, primesv5);
}

void BM_PrimesV6(benchmark::State &state)
{
    BM_Sieve(state, primesv6);
}
void BM_PrimesV7(benchmark::State &state)
{
    BM_Sieve(state, primesv7);
}

void BM_PrimesV8(benchmark::State &state)
{
    BM_Sieve(state, primesv8);
}


inline constexpr std::uint32_t MAX = std::numeric_limits<std::uint32_t>::max();


// BENCHMARK(BM_EratosthenesSkip2)->Arg(MAX)->Unit(benchmark::kMillisecond);
// BENCHMARK(BM_PrimesV5)->Arg(MAX)->Unit(benchmark::kMillisecond);
// BENCHMARK(BM_PrimesV6)->Arg(MAX)->Unit(benchmark::kMillisecond);
// BENCHMARK(BM_PrimesV7)->Arg(MAX)->Unit(benchmark::kMillisecond)->Iterations(5);
BENCHMARK(BM_PrimesV8)->Arg(MAX)->Unit(benchmark::kMillisecond)->Iterations(5);

// BENCHMARK(BM_EulerSkip2)->Arg(MAX)->Unit(benchmark::kMillisecond);

// BENCHMARK(BM_PrimesV6)->Arg()->Unit(benchmark::kMillisecond);


BENCHMARK_MAIN();