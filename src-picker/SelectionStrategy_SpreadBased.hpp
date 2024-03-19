#ifndef PICKER_SELECTION_STRATEGY_SPREAD_BASED_HPP
#define PICKER_SELECTION_STRATEGY_SPREAD_BASED_HPP

#include <memory>
#include <string>

#include "ProblemData.hpp"
#include "SelectionStrategy.hpp"

namespace picker {

struct TeamData;

class RandomizationStrategy;

class SpreadBasedStrategy : public SelectionStrategy
{
public:
  using TeamDataLookup = picker::ProblemData::TeamDataLookup;

  SpreadBasedStrategy(std::unique_ptr<RandomizationStrategy>&& inRand, const TeamDataLookup* inTeamDataLookup);

  std::string selectWinner(const std::string& team1, const std::string& team2) const override;

private:
  std::unique_ptr<RandomizationStrategy> rand;

  const TeamDataLookup* teamDataLookup;
};

}// namespace picker

#endif