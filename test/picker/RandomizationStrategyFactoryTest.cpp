#include <memory>
#include <string_view>

#include "catch2/catch_test_macros.hpp"
#include "nlohmann/json.hpp"

#include "Constants.hpp"
#include "RandomizationStrategy_Factory.hpp"
#include "RandomizationStrategy_MersenneTwister.hpp"
#include "RandomizationStrategy_MinStdRand.hpp"
#include "RandomizationStrategy_StdRand.hpp"

TEST_CASE("RandomizationStrategyFactory - create strategies", "[RandomizationStrategyFactory]")// NOLINT
{
  picker::RandomizationStrategyFactory factory{ };
  factory.registerFactory(
    picker::MERSENNE_TWISTER_STRATEGY_LABEL, std::make_unique<picker::MersenneTwisterStrategyFactory>( ));
  factory.registerFactory(picker::MINSTD_RAND_STRATEGY_LABEL, std::make_unique<picker::MinStdRandStrategyFactory>( ));
  factory.registerFactory(picker::STD_RAND_STRATEGY_LABEL, std::make_unique<picker::StdRandStrategyFactory>( ));

  // NOLINTBEGIN
  constexpr std::string_view unregisteredFactoryLabel{ "unregistered" };
  const nlohmann::json params{ };
  CHECK(factory.create(unregisteredFactoryLabel, params) == nullptr);
  CHECK(std::dynamic_pointer_cast<picker::MersenneTwisterStrategy>(
          factory.create(picker::MERSENNE_TWISTER_STRATEGY_LABEL, params))
        != nullptr);
  CHECK(
    std::dynamic_pointer_cast<picker::MinStdRandStrategy>(factory.create(picker::MINSTD_RAND_STRATEGY_LABEL, params))
    != nullptr);
  CHECK(std::dynamic_pointer_cast<picker::StdRandStrategy>(factory.create(picker::STD_RAND_STRATEGY_LABEL, params))
        != nullptr);
  // NOLINTEND
}
