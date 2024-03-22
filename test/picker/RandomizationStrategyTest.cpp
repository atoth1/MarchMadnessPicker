#include <random>

#include "catch2/catch_test_macros.hpp"

#include "RandomizationStrategy.hpp"
#include "RandomizationStrategy_MersenneTwister.hpp"
#include "RandomizationStrategy_MinStdRand.hpp"
#include "RandomizationStrategy_StdRand.hpp"

namespace {
void testRandomizationStrategy(picker::RandomizationStrategy& strategy)
{
  constexpr int TIMES = 10;
  for (int count = 0; count < TIMES; ++count) {
    const double num = strategy.getRandom( );
    CHECK(num >= 0.0);// NOLINT(cppcoreguidelines-avoid-do-while)
    CHECK(num <= 1.0);// NOLINT(cppcoreguidelines-avoid-do-while)
  }
}

}// namespace

// NOLINTNEXTLINE(misc-use-anonymous-namespace)
TEST_CASE("RandomizationStrategy - numbers in correct range", "[RandomizationStrategy]")
{
  picker::MersenneTwisterStrategy mersenne(std::random_device{ }( ));
  testRandomizationStrategy(mersenne);

  picker::MinStdRandStrategy minStdRand(std::random_device{ }( ));
  testRandomizationStrategy(minStdRand);

  picker::StdRandStrategy stdRand(std::random_device{ }( ));
  testRandomizationStrategy(stdRand);
}