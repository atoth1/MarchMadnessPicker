#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "fmt/core.h"
#include "fmt/ranges.h"// NOLINT(misc-include-cleaner)
#include "nlohmann/json.hpp"

#include "BracketData.hpp"
#include "LogManager.hpp"
#include "ProblemData.hpp"
#include "TeamData.hpp"

void picker::ProblemData::validate( ) const
{
  auto validateRegion = [this](const picker::RegionData& regionData) {
    std::vector<std::string_view> unmatchedNames{ };
    for (const auto& teamName : regionData.teams) {
      if (auto teamDataIt = this->teamDataLookup->find(teamName); teamDataIt == this->teamDataLookup->end( )) {
        unmatchedNames.push_back(teamName);
      }
    }

    if (!unmatchedNames.empty( )) {
      logError(fmt::format(
        "The following team names were not found in the team_data_file (check for misspellings): {}", unmatchedNames));
      throw std::runtime_error(R"(ERROR - Mismatched team names between "bracket_data" and "team_data_file".")");
    }

    bool allSeedsCorrect = true;
    int seed = 1;
    for (const auto& teamName : regionData.teams) {
      const auto& data = this->teamDataLookup->at(teamName);
      if (data.seed && *data.seed != seed) {
        logError(
          fmt::format("Seed value {} for team {} in bracket_data does not match its seed value {} in team_data_file",
            seed,
            teamName,
            *data.seed));
        allSeedsCorrect = false;
      }
      ++seed;
    }

    if (!allSeedsCorrect) {
      throw std::runtime_error(R"(ERROR - Mismatched seeding between "bracket_data" and "team_data_file".")");
    }
  };

  logDebug("Validating top_left bracket data.");
  validateRegion(bracketData.topLeft);
  logDebug("Validating bottom_left bracket data.");
  validateRegion(bracketData.bottomLeft);
  logDebug("Validating top_right bracket data.");
  validateRegion(bracketData.topRight);
  logDebug("Validating bottom_right bracket data.");
  validateRegion(bracketData.bottomRight);
}

bool picker::ProblemData::operator==(const picker::ProblemData& other) const noexcept
{
  auto equalLookups = [](const auto& lookup1, const auto& lookup2) {
    return (!lookup1 && !lookup2) || (lookup1 && lookup2 && *lookup1 == *lookup2);
  };
  return bracketData == other.bracketData && equalLookups(teamDataLookup, other.teamDataLookup)
         && selectionStrategy == other.selectionStrategy && selectionStrategyParams == other.selectionStrategyParams
         && randomizationStrategy == other.randomizationStrategy
         && randomizationStrategyParams == other.randomizationStrategyParams && outputStrategy == other.outputStrategy
         && outputStrategyParams == other.outputStrategyParams;
}

void picker::from_json(const nlohmann::json& input, picker::ProblemData& output)// NOLINT(misc-include-cleaner)
{
  logDebug("Parsing problem data.");

  input.at("bracket_data").get_to(output.bracketData);

  auto makeTeamDataLookup = [&]( ) {
    const auto teamDataFile = input.at("team_data_file").template get<std::string>( );
    std::ifstream teamDataStream(teamDataFile);
    const auto parsedTeamData = nlohmann::json::parse(teamDataStream);// NOLINT(misc-include-cleaner)

    std::vector<picker::TeamData> teamData{ };
    parsedTeamData.get_to(teamData);

    auto lookup = std::make_shared<ProblemData::TeamDataLookup>( );
    for (const auto& data : teamData) { (*lookup)[data.teamName] = data; }
    return lookup;
  };
  output.teamDataLookup = makeTeamDataLookup( );

  if (input.contains("selection_strategy")) { input.at("selection_strategy").get_to(output.selectionStrategy); }

  if (input.contains("selection_strategy_params")) {
    output.selectionStrategyParams = input.at("selection_strategy_params");
  }

  if (input.contains("randomization_strategy")) {
    input.at("randomization_strategy").get_to(output.randomizationStrategy);
  }

  if (input.contains("randomization_strategy_params")) {
    output.randomizationStrategyParams = input.at("randomization_strategy_params");
  }

  if (input.contains("output_strategy")) { input.at("output_strategy").get_to(output.outputStrategy); }

  if (input.contains("output_strategy_params")) { output.outputStrategyParams = input.at("output_strategy_params"); }
}
