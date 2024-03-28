#include <memory>
#include <string>
#include <utility>

#include "fmt/core.h"
#include "nlohmann/json.hpp"// NOLINT(misc-include-cleaner)

#include "LogManager.hpp"
#include "SelectionStrategy.hpp"
#include "SelectionStrategy_RankDeterministic.hpp"
#include "TeamData.hpp"

picker::RankDeterministicStrategy::RankDeterministicStrategy(TeamDataLookupPtr inTeamDataLookup)
  : teamDataLookup(std::move(inTeamDataLookup))
{}

std::string picker::RankDeterministicStrategy::selectWinner(const std::string& team1, const std::string& team2) const
{
  const TeamData& teamData1 = teamDataLookup->at(team1);
  const TeamData& teamData2 = teamDataLookup->at(team2);
  std::string winner = teamData1.rank < teamData2.rank ? team1 : team2;
  logDebug(fmt::format("In matchup {} vs {}, {} advances ({} rank = {}, {} rank = {}).",
    teamData1.teamName,
    teamData2.teamName,
    winner,
    teamData1.teamName,
    teamData1.rank,
    teamData2.teamName,
    teamData2.rank));
  return winner;
}

std::shared_ptr<picker::SelectionStrategy> picker::RankDeterministicStrategyFactory::create(
  const nlohmann::json& /*params*/,// NOLINT(misc-include-cleaner)
  const RandomizationStrategyPtr& /*randomizationStrategy*/,
  const TeamDataLookupPtr& teamDataLookup) const
{
  return std::make_shared<RankDeterministicStrategy>(teamDataLookup);
}
