#include <memory>
#include <string_view>

#include "catch2/catch_test_macros.hpp"
#include "nlohmann/json.hpp"

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
    picker::SelectionStrategyFactory::COIN_FLIP_LABEL, std::make_unique<picker::CoinFlipStrategyFactory>(randStrategy));
  factory.registerFactory(picker::SelectionStrategyFactory::RANK_DETERMINISTIC_LABEL,
    std::make_unique<picker::RankDeterministicStrategyFactory>(&teamDataLookup));
  factory.registerFactory(picker::SelectionStrategyFactory::SPREAD_BASED_LABEL,
    std::make_unique<picker::SpreadBasedStrategyFactory>(randStrategy, &teamDataLookup));

  // NOLINTBEGIN
  constexpr std::string_view unregisteredFactoryLabel{ "unregistered" };
  const nlohmann::json params{ };
  CHECK(factory.create(unregisteredFactoryLabel, params) == nullptr);
  CHECK(std::dynamic_pointer_cast<picker::CoinFlipStrategy>(
          factory.create(picker::SelectionStrategyFactory::COIN_FLIP_LABEL, params))
        != nullptr);
  CHECK(std::dynamic_pointer_cast<picker::RankDeterministicStrategy>(
          factory.create(picker::SelectionStrategyFactory::RANK_DETERMINISTIC_LABEL, params))
        != nullptr);
  CHECK(std::dynamic_pointer_cast<picker::SpreadBasedStrategy>(
          factory.create(picker::SelectionStrategyFactory::SPREAD_BASED_LABEL, params))
        != nullptr);
  // NOLINTEND
}
