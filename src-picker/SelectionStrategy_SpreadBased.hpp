#ifndef PICKER_SELECTION_STRATEGY_SPREAD_BASED_HPP
#define PICKER_SELECTION_STRATEGY_SPREAD_BASED_HPP

#include <memory>
#include <string>

#include "nlohmann/json_fwd.hpp"

#include "GenericFactory.hpp"
#include "ProblemData.hpp"
#include "SelectionStrategy.hpp"

namespace picker {

class RandomizationStrategy;

class SpreadBasedStrategy : public SelectionStrategy
{
public:
  using TeamDataLookup = ProblemData::TeamDataLookup;

  SpreadBasedStrategy(const std::shared_ptr<RandomizationStrategy>& inRand, const TeamDataLookup* inTeamDataLookup);

  std::string selectWinner(const std::string& team1, const std::string& team2) const override;

private:
  std::shared_ptr<RandomizationStrategy> rand;

  const TeamDataLookup* teamDataLookup;
};

class SpreadBasedStrategyFactory : public GenericFactory<SelectionStrategy>
{
public:
  using TeamDataLookup = ProblemData::TeamDataLookup;

  SpreadBasedStrategyFactory(const std::shared_ptr<RandomizationStrategy>& inRand,
    const TeamDataLookup* inTeamDataLookup);

  std::shared_ptr<SelectionStrategy> create(const nlohmann::json& params) const override;

private:
  std::shared_ptr<RandomizationStrategy> rand;

  const TeamDataLookup* teamDataLookup;
};

}// namespace picker

#endif
