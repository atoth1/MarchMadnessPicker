#ifndef PICKER_SELECTION_STRATEGY_SPREAD_BASED_HPP
#define PICKER_SELECTION_STRATEGY_SPREAD_BASED_HPP

#include <memory>
#include <string>

#include "nlohmann/json_fwd.hpp"

#include "GenericFactory.hpp"
#include "SelectionStrategy.hpp"
#include "SelectionStrategy_Factory.hpp"

namespace picker {

class RandomizationStrategy;

class SpreadBasedStrategy : public SelectionStrategy
{
public:
  using RandomizationStrategyPtr = SelectionStrategyFactory::RandomizationStrategyPtr;

  using TeamDataLookupPtr = SelectionStrategyFactory::TeamDataLookupPtr;

  SpreadBasedStrategy(RandomizationStrategyPtr inRand, TeamDataLookupPtr inTeamDataLookup);

  std::string selectWinner(const std::string& team1, const std::string& team2) const override;

private:
  RandomizationStrategyPtr rand;

  TeamDataLookupPtr teamDataLookup;
};

class SpreadBasedStrategyFactory : public SelectionStrategyFactory::FactoryType
{
public:
  using RandomizationStrategyPtr = SelectionStrategyFactory::RandomizationStrategyPtr;

  using TeamDataLookupPtr = SelectionStrategyFactory::TeamDataLookupPtr;

  std::shared_ptr<SelectionStrategy> create(const nlohmann::json& params,
    const RandomizationStrategyPtr& randomizationStrategy,
    const TeamDataLookupPtr& teamDataLookup) const override;
};

}// namespace picker

#endif
