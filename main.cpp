#include "Concurrent/find_primesv3.hpp"
#include "Concurrent/find_primesv2.hpp"
#include "Concurrent/find_primesv4.hpp"
#include "Concurrent/find_primesv5.hpp"


#include "Sequential/prime_seq.hpp"
#include "Sequential/sieve_of_aktin.hpp"
#include "Sequential/sieve_of_sundaram.hpp"
#include "Sequential/sieve_of_eratosthenes.hpp"
#include "Sequential/sieve_of_euler.hpp"


#include <iostream>
#include <benchmark/benchmark.h>




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


// BENCHMARK(BM_Eratosthenes)->RangeMultiplier(2)->Range(1U << 24U, 1U << 30U)->MeasureProcessCPUTime()->Complexity()->UseRealTime()->Unit(benchmark::kMillisecond);
// BENCHMARK(BM_Euler)->RangeMultiplier(2)->Range(1U << 24U, 1U << 30U)->MeasureProcessCPUTime()->Complexity()->UseRealTime()->Unit(benchmark::kMillisecond);
// BENCHMARK(BM_Aktin)->RangeMultiplier(2)->Range(1U << 24U, 1U << 30U)->MeasureProcessCPUTime()->Complexity()->UseRealTime()->Unit(benchmark::kMillisecond);
// BENCHMARK(BM_Sundaram)->RangeMultiplier(2)->Range(1U << 24U, 1U << 30U)->MeasureProcessCPUTime()->Complexity()->UseRealTime()->Unit(benchmark::kMillisecond);

// BENCHMARK(BM_Eratosthenes)->Arg(1'000'000'000)->Unit(benchmark::kMillisecond);
// BENCHMARK(BM_EratosthenesSkip2)->Arg(1'000'000'000)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_EulerSkip2)->Arg(1'000'000'000)->Unit(benchmark::kMillisecond)->MeasureProcessCPUTime()->Complexity()->UseRealTime();
BENCHMARK(BM_PrimesV5)->Arg(1'000'000'000)->Unit(benchmark::kMillisecond)->MeasureProcessCPUTime()->Complexity()->UseRealTime();
BENCHMARK(BM_PrimesV4)->Arg(1'000'000'000)->Unit(benchmark::kMillisecond)->MeasureProcessCPUTime()->Complexity()->UseRealTime();


BENCHMARK_MAIN();