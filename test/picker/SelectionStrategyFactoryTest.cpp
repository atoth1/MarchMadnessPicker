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

TEST_CASE("SelectionStrategyFactory - create strategies", "[SelectionStrategyFactory]")// NOLINT
{
  constexpr double randValue = 0.42;
  const auto randStrategy = std::make_shared<DeterministicStrategy>(randValue);
  const picker::ProblemData::TeamDataLookup teamDataLookup{ };

  picker::SelectionStrategyFactory factory{ };
  factory.registerFactory(
    picker::COIN_FLIP_STRATEGY_LABEL, std::make_unique<picker::CoinFlipStrategyFactory>(randStrategy));
  factory.registerFactory(picker::RANK_DETERMINISTIC_STRATEGY_LABEL,
    std::make_unique<picker::RankDeterministicStrategyFactory>(&teamDataLookup));
  factory.registerFactory(picker::SPREAD_BASED_STRATEGY_LABEL,
    std::make_unique<picker::SpreadBasedStrategyFactory>(randStrategy, &teamDataLookup));

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
