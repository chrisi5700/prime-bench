#include <gtest/gtest.h>
#include "sieve_of_aktin.hpp"
#include "sieve_of_sundaram.hpp"
#include "sieve_of_euler.hpp"
#include "sieve_of_eratosthenes.hpp"
#include "prime_seq.hpp"
#include "test_utils.hpp"

// Test files are a mess for the linter because I have no control over the google-test macros :/

TEST(FindPrimes, NaiveImpl)
{
    using pvec = std::vector<std::uint32_t>;
    pvec primes8 = {2, 3, 5, 7};
    pvec primes16 = {2, 3, 5, 7, 11, 13};
    pvec primes32 = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    pvec res8 = find_primes_seq<std::uint32_t, 2, 3, 5>(8);
    pvec res16 = find_primes_seq<std::uint32_t, 2, 3, 5>(16);
    pvec res32 = find_primes_seq<std::uint32_t, 2, 3, 5>(32);
    EXPECT_EQ(primes8, res8) << "Primes differ \t" << get_diff(primes8, res8) << '\n';
    EXPECT_EQ(primes16, res16) << "Primes differ \t" << get_diff(primes16, res16) << '\n';
    EXPECT_EQ(primes32, res32) << "Primes differ \t" << get_diff(primes32, res32) << '\n';
}

void test_sieve_impl(auto sieve_fun)
{
    for (std::uint32_t i = 8; i < (1U << 22U); i = i << 1)
    {
        auto primes_guaranteed = find_primes_seq<std::uint32_t, 2, 3, 5>(i);
        auto primes_tested = sieve_fun(i);
        ASSERT_EQ(primes_guaranteed.size(), primes_tested.size()) << "Primes differ for i = " << i  
        << " Differing primes are: " << get_diff(primes_tested, primes_guaranteed) << '\n';
    }
}

TEST(FindPrimes, SieveOfAktin)  
{
    test_sieve_impl(sieve_of_aktin<std::uint32_t>);
}

TEST(FindPrimes, SieveOfAktin2)  
{
    test_sieve_impl(sieve_of_aktin2<std::uint32_t>);
}

TEST(FindPrimes, SieveOfSundaram)  
{
    test_sieve_impl(sieve_of_sundaram<std::uint32_t>);
}

TEST(FindPrimes, SieveOfEratosthenes)  
{
    test_sieve_impl(sieve_of_eratosthenes<std::uint32_t>);
}

TEST(FindPrimes, SieveOfEuler)  
{
    test_sieve_impl(sieve_of_euler<std::uint32_t>);
}

TEST(FindPrimes, SieveOfErastosthenesSkip2)
{
    test_sieve_impl(sieve_of_eratosthenes_skip2<std::uint32_t>);
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}