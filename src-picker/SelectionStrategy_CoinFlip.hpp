#ifndef PICKER_SELECTION_STRATEGY_COIN_FLIP_HPP
#define PICKER_SELECTION_STRATEGY_COIN_FLIP_HPP

#include <memory>
#include <string>

#include "nlohmann/json_fwd.hpp"

#include "GenericFactory.hpp"
#include "SelectionStrategy.hpp"
#include "SelectionStrategy_Factory.hpp"

namespace picker {

class RandomizationStrategy;

class CoinFlipStrategy : public SelectionStrategy
{
public:
using RandomizationStrategyPtr = SelectionStrategyFactory::RandomizationStrategyPtr;

  explicit CoinFlipStrategy(RandomizationStrategyPtr inRand);

  std::string selectWinner(const std::string& team1, const std::string& team2) const override;

private:
  static constexpr double THRESH = 0.5;

  std::shared_ptr<RandomizationStrategy> rand;
};

class CoinFlipStrategyFactory : public SelectionStrategyFactory::FactoryType

{
public:
  using RandomizationStrategyPtr = SelectionStrategyFactory::RandomizationStrategyPtr;

  using TeamDataLookupPtr = SelectionStrategyFactory::TeamDataLookupPtr;

  CoinFlipStrategyFactory( ) = default;

  std::shared_ptr<SelectionStrategy> create(const nlohmann::json& params,
    const RandomizationStrategyPtr& randomizationStrategy,
    const TeamDataLookupPtr& teamDataLookup) const override;
};

}// namespace picker

#endif
