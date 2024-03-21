#ifndef PICKER_SELECTION_STRATEGY_RANK_DETERMINISTIC_HPP
#define PICKER_SELECTION_STRATEGY_RANK_DETERMINISTIC_HPP

#include <memory>
#include <string>

#include "nlohmann/json_fwd.hpp"

#include "GenericFactory.hpp"
#include "ProblemData.hpp"
#include "SelectionStrategy.hpp"
#include "SelectionStrategy_Factory.hpp"

namespace picker {

class RandomizationStrategy;

class RankDeterministicStrategy : public SelectionStrategy
{
public:
  using TeamDataLookupPtr = SelectionStrategyFactory::TeamDataLookupPtr;

  explicit RankDeterministicStrategy(TeamDataLookupPtr inTeamDataLookup);

  std::string selectWinner(const std::string& team1, const std::string& team2) const override;

private:
  TeamDataLookupPtr teamDataLookup;
};

class RankDeterministicStrategyFactory : public SelectionStrategyFactory::FactoryType
{
public:
  using RandomizationStrategyPtr = SelectionStrategyFactory::RandomizationStrategyPtr;

  using TeamDataLookupPtr = SelectionStrategyFactory::TeamDataLookupPtr;

  RankDeterministicStrategyFactory( ) = default;

  std::shared_ptr<SelectionStrategy> create(const nlohmann::json& params,
    const RandomizationStrategyPtr& randomizationStrategy,
    const TeamDataLookupPtr& teamDataLookup) const override;
};

}// namespace picker

#endif
