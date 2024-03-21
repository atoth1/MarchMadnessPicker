#include <memory>
#include <string_view>

#include "catch2/catch_test_macros.hpp"
#include "nlohmann/json.hpp"

#include "Constants.hpp"
#include "ProblemData.hpp"
#include "SelectionStrategy_CoinFlip.hpp"
#include "SelectionStrategy_Factory.hpp"
#include "SelectionStrategy_RankDeterministic.hpp"
#include "SelectionStrategy_SpreadBased.hpp"
#include "TestUtils.hpp"

namespace {
picker::SelectionStrategyFactory getTestFactory( )
{
  picker::SelectionStrategyFactory factory{ };
  factory.registerFactory(picker::COIN_FLIP_STRATEGY_LABEL, std::make_unique<picker::CoinFlipStrategyFactory>( ));
  factory.registerFactory(
    picker::RANK_DETERMINISTIC_STRATEGY_LABEL, std::make_unique<picker::RankDeterministicStrategyFactory>( ));
  factory.registerFactory(picker::SPREAD_BASED_STRATEGY_LABEL, std::make_unique<picker::SpreadBasedStrategyFactory>( ));
  return factory;
}
}// namespace

TEST_CASE("SelectionStrategyFactory - unset requirements", "[SelectionStrategyFactory]")// NOLINT
{
  const auto factory1 = getTestFactory( );
  const nlohmann::json params{ };
  CHECK(factory1.create(picker::SPREAD_BASED_STRATEGY_LABEL, params) == nullptr);// NOLINT

  auto factory2 = getTestFactory( );
  constexpr double randValue = 0.42;
  const auto randStrategy = std::make_shared<DeterministicStrategy>(randValue);
  factory2.setRandomizationStrategy(randStrategy);
  CHECK(factory2.create(picker::SPREAD_BASED_STRATEGY_LABEL, params) == nullptr);// NOLINT

  auto factory3 = getTestFactory( );
  const auto teamDataLookup = std::make_shared<picker::ProblemData::TeamDataLookup>( );
  factory3.setTeamDataLookup(teamDataLookup);
  CHECK(factory3.create(picker::SPREAD_BASED_STRATEGY_LABEL, params) == nullptr);// NOLINT
}

TEST_CASE("SelectionStrategyFactory - create strategies", "[SelectionStrategyFactory]")// NOLINT
{
  auto factory = getTestFactory( );
  constexpr double randValue = 0.42;
  const auto randStrategy = std::make_shared<DeterministicStrategy>(randValue);
  const auto teamDataLookup = std::make_shared<picker::ProblemData::TeamDataLookup>( );
  factory.setRandomizationStrategy(randStrategy);
  factory.setTeamDataLookup(teamDataLookup);

  // NOLINTBEGIN
  constexpr std::string_view unregisteredFactoryLabel{ "unregistered" };
  const nlohmann::json params{ };
  CHECK(factory.create(unregisteredFactoryLabel, params) == nullptr);
  CHECK(std::dynamic_pointer_cast<picker::CoinFlipStrategy>(factory.create(picker::COIN_FLIP_STRATEGY_LABEL, params))
        != nullptr);
  CHECK(std::dynamic_pointer_cast<picker::RankDeterministicStrategy>(
          factory.create(picker::RANK_DETERMINISTIC_STRATEGY_LABEL, params))
        != nullptr);
  CHECK(
    std::dynamic_pointer_cast<picker::SpreadBasedStrategy>(factory.create(picker::SPREAD_BASED_STRATEGY_LABEL, params))
    != nullptr);
  // NOLINTEND
}
