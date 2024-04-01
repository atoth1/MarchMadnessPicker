#include <memory>
#include <string_view>

#include "catch2/catch_test_macros.hpp"
#include "nlohmann/json.hpp"//NOLINT(misc-include-cleaner)

#include "Constants.hpp"
#include "RandomizationStrategy_Factory.hpp"
#include "RandomizationStrategy_MersenneTwister.hpp"
#include "RandomizationStrategy_MinStdRand.hpp"
#include "RandomizationStrategy_StdRand.hpp"

// NOLINTNEXTLINE(misc-use-anonymous-namespace)
TEST_CASE("RandomizationStrategyFactory - create mersenne twister strategy", "[RandomizationStrategyFactory]")
{
  const picker::MersenneTwisterStrategyFactory factory{ };
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
  CHECK(std::dynamic_pointer_cast<picker::MersenneTwisterStrategy>(factory.create({ })) != nullptr);
}

// NOLINTNEXTLINE(misc-use-anonymous-namespace)
TEST_CASE("RandomizationStrategyFactory - create minstd-rand strategy", "[RandomizationStrategyFactory]")
{
  const picker::MinStdRandStrategyFactory factory{ };
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
  CHECK(std::dynamic_pointer_cast<picker::MinStdRandStrategy>(factory.create({ })) != nullptr);
}

// NOLINTNEXTLINE(misc-use-anonymous-namespace)
TEST_CASE("RandomizationStrategyFactory - create std-rand strategy", "[RandomizationStrategyFactory]")
{
  const picker::StdRandStrategyFactory factory{ };
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
  CHECK(std::dynamic_pointer_cast<picker::StdRandStrategy>(factory.create({ })) != nullptr);
}

// NOLINTNEXTLINE(misc-use-anonymous-namespace)
TEST_CASE("RandomizationStrategyFactory - create strategies", "[RandomizationStrategyFactory]")
{
  picker::RandomizationStrategyFactory factory{ };
  factory.registerFactory(
    picker::MERSENNE_TWISTER_STRATEGY_LABEL, std::make_unique<picker::MersenneTwisterStrategyFactory>( ));
  factory.registerFactory(picker::MINSTD_RAND_STRATEGY_LABEL, std::make_unique<picker::MinStdRandStrategyFactory>( ));
  factory.registerFactory(picker::STD_RAND_STRATEGY_LABEL, std::make_unique<picker::StdRandStrategyFactory>( ));

  constexpr std::string_view unregisteredFactoryLabel{ "unregistered" };
  const nlohmann::json params{ };// NOLINT(misc-include-cleaner)
  // NOLINTBEGIN(cppcoreguidelines-avoid-do-while)
  CHECK(factory.create(unregisteredFactoryLabel, params) == nullptr);
  CHECK(std::dynamic_pointer_cast<picker::MersenneTwisterStrategy>(
          factory.create(picker::MERSENNE_TWISTER_STRATEGY_LABEL, params))
        != nullptr);
  CHECK(
    std::dynamic_pointer_cast<picker::MinStdRandStrategy>(factory.create(picker::MINSTD_RAND_STRATEGY_LABEL, params))
    != nullptr);
  CHECK(std::dynamic_pointer_cast<picker::StdRandStrategy>(factory.create(picker::STD_RAND_STRATEGY_LABEL, params))
        != nullptr);
  // NOLINTEND(cppcoreguidelines-avoid-do-while)
}
