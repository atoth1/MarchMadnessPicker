#include <memory>
#include <string>
#include <utility>

#include "nlohmann/json.hpp"// NOLINT(misc-include-cleaner)

#include "SelectionStrategy.hpp"
#include "SelectionStrategy_RankDeterministic.hpp"

picker::RankDeterministicStrategy::RankDeterministicStrategy(TeamDataLookupPtr inTeamDataLookup)
  : teamDataLookup(std::move(inTeamDataLookup))
{}

std::string picker::RankDeterministicStrategy::selectWinner(const std::string& team1, const std::string& team2) const
{
  return teamDataLookup->at(team1).rank < teamDataLookup->at(team2).rank ? team1 : team2;
}

std::shared_ptr<picker::SelectionStrategy> picker::RankDeterministicStrategyFactory::create(
  const nlohmann::json& /*params*/,// NOLINT(misc-include-cleaner)
  const RandomizationStrategyPtr& /*randomizationStrategy*/,
  const TeamDataLookupPtr& teamDataLookup) const
{
  return std::make_shared<RankDeterministicStrategy>(teamDataLookup);
}
