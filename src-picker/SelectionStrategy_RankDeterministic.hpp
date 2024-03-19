#ifndef PICKER_SELECTION_STRATEGY_RANK_DETERMINISTIC_HPP
#define PICKER_SELECTION_STRATEGY_RANK_DETERMINISTIC_HPP

#include <string>

#include "ProblemData.hpp"
#include "SelectionStrategy.hpp"

namespace picker {

struct TeamData;

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

}// namespace picker

#endif