#include <memory>
#include <string>
#include <utility>

#include "fmt/core.h"
#include "nlohmann/json.hpp"// NOLINT(misc-include-cleaner)

#include "LogManager.hpp"
#include "RandomizationStrategy.hpp"// NOLINT(misc-include-cleaner)
#include "SelectionStrategy.hpp"
#include "SelectionStrategy_CoinFlip.hpp"

picker::CoinFlipStrategy::CoinFlipStrategy(RandomizationStrategyPtr inRand) : rand(std::move(inRand)) {}

std::string picker::CoinFlipStrategy::selectWinner(const std::string& team1, const std::string& team2) const
{
  std::string winner = rand->getRandom( ) < THRESH ? team1 : team2;
  logDebug(fmt::format("In matchup {} vs {}, {} advances.", team1, team2, winner));
  return winner;
}

// NOLINTNEXTLINE(misc-include-cleaner)
std::shared_ptr<picker::SelectionStrategy> picker::CoinFlipStrategyFactory::create(const nlohmann::json& /*params*/,
  const RandomizationStrategyPtr& randomizationStrategy,
  const TeamDataLookupPtr& /*teamDataLookup*/) const
{
  return std::make_shared<CoinFlipStrategy>(randomizationStrategy);
}
