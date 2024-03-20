#include <memory>
#include <string>

#include "RandomizationStrategy.hpp"
#include "SelectionStrategy.hpp"
#include "SelectionStrategy_CoinFlip.hpp"

// NOLINTNEXTLINE
picker::CoinFlipStrategy::CoinFlipStrategy(const std::shared_ptr<RandomizationStrategy>& inRand) : rand(inRand) {}

std::string picker::CoinFlipStrategy::selectWinner(const std::string& team1, const std::string& team2) const
{
  return rand->getRandom( ) < THRESH ? team1 : team2;
}

// NOLINTBEGIN
picker::CoinFlipStrategyFactory::CoinFlipStrategyFactory(const std::shared_ptr<RandomizationStrategy>& inRand)
  : rand(inRand)
{}
// NOLINTEND

std::shared_ptr<picker::SelectionStrategy> picker::CoinFlipStrategyFactory::create(
  const nlohmann::json& /*params*/) const
{
  return std::make_shared<CoinFlipStrategy>(rand);
}
