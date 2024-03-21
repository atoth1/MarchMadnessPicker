#include <memory>
#include <string>
#include <utility>

#include "nlohmann/json.hpp"

#include "RandomizationStrategy.hpp"
#include "SelectionStrategy.hpp"
#include "SelectionStrategy_CoinFlip.hpp"

picker::CoinFlipStrategy::CoinFlipStrategy(RandomizationStrategyPtr inRand) : rand(std::move(inRand)) {}

std::string picker::CoinFlipStrategy::selectWinner(const std::string& team1, const std::string& team2) const
{
  return rand->getRandom( ) < THRESH ? team1 : team2;
}

std::shared_ptr<picker::SelectionStrategy> picker::CoinFlipStrategyFactory::create(const nlohmann::json& /*params*/,
  const RandomizationStrategyPtr& randomizationStrategy,
  const TeamDataLookupPtr& /*teamDataLookup*/) const
{
  return std::make_shared<CoinFlipStrategy>(randomizationStrategy);
}
