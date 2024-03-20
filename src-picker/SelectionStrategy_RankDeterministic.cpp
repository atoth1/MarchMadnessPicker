#include <memory>
#include <string>

#include "SelectionStrategy.hpp"
#include "SelectionStrategy_RankDeterministic.hpp"
#include "TeamData.hpp"

picker::RankDeterministicStrategy::RankDeterministicStrategy(const TeamDataLookup* inTeamDataLookup)
  : teamDataLookup(inTeamDataLookup)
{}

std::string picker::RankDeterministicStrategy::selectWinner(const std::string& team1, const std::string& team2) const
{
  return teamDataLookup->at(team1).rank < teamDataLookup->at(team2).rank ? team1 : team2;
}

picker::RankDeterministicStrategyFactory::RankDeterministicStrategyFactory(const TeamDataLookup* inTeamDataLookup)
  : teamDataLookup(inTeamDataLookup)
{}

std::shared_ptr<picker::SelectionStrategy> picker::RankDeterministicStrategyFactory::create(
  const nlohmann::json& /*params*/) const
{
  return std::make_shared<RankDeterministicStrategy>(teamDataLookup);
}
