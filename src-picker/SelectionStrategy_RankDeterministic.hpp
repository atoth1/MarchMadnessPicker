#ifndef PICKER_SELECTION_STRATEGY_RANK_DETERMINISTIC_HPP
#define PICKER_SELECTION_STRATEGY_RANK_DETERMINISTIC_HPP

#include <memory>
#include <string>

#include "nlohmann/json_fwd.hpp"

#include "GenericFactory.hpp"
#include "ProblemData.hpp"
#include "SelectionStrategy.hpp"

namespace picker {

class RandomizationStrategy;

class RankDeterministicStrategy : public SelectionStrategy
{
public:
  using TeamDataLookup = picker::ProblemData::TeamDataLookup;

  explicit RankDeterministicStrategy(const TeamDataLookup* inTeamDataLookup);

  std::string selectWinner(const std::string& team1, const std::string& team2) const override;

private:
  const TeamDataLookup* teamDataLookup;
};

class RankDeterministicStrategyFactory : public GenericFactory<SelectionStrategy>
{
public:
  using TeamDataLookup = ProblemData::TeamDataLookup;

  RankDeterministicStrategyFactory(const TeamDataLookup* inTeamDataLookup);

  std::shared_ptr<SelectionStrategy> create(const nlohmann::json& params) const override;

private:
  const TeamDataLookup* teamDataLookup;
};

}// namespace picker

#endif
