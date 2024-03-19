#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

#include "BracketData.hpp"
#include "ProblemData.hpp"
#include "TeamData.hpp"

void picker::ProblemData::validate( ) const
{
  auto validateRegion = [this](const picker::RegionData& regionData) {
    bool allTeamNamesFound = true;
    for (const auto& teamName : regionData.teams) {
      if (auto teamDataIt = this->teamDataLookup.find(teamName); teamDataIt == this->teamDataLookup.end( )) {
        allTeamNamesFound = false;
      }
    }

    if (!allTeamNamesFound) {
      throw std::runtime_error(R"(ERROR - Mismatched team names between "bracket_data" and "team_data_file".")");
    }

    bool allSeedsCorrect = true;
    int seed = 1;
    for (const auto& teamName : regionData.teams) {
      const auto& data = this->teamDataLookup.at(teamName);
      if (data.seed != seed) { allSeedsCorrect = false; }
      ++seed;
    }

    if (!allSeedsCorrect) {
      throw std::runtime_error(R"(ERROR - Mismatched seeding between "bracket_data" and "team_data_file".")");
    }
  };

  validateRegion(bracketData.topLeft);
  validateRegion(bracketData.bottomLeft);
  validateRegion(bracketData.topRight);
  validateRegion(bracketData.bottomRight);
}

void picker::from_json(const nlohmann::json& input, picker::ProblemData& output)
{
  input.at("bracket_data").get_to(output.bracketData);

  auto makeTeamDataLookup = [&]( ) {
    const auto teamDataFile = input.at("team_data_file").template get<std::string>( );
    std::ifstream teamDataStream(teamDataFile);
    const auto parsedTeamData = nlohmann::json::parse(teamDataStream);

    std::vector<picker::TeamData> teamData{ };
    parsedTeamData.get_to(teamData);

    picker::ProblemData::TeamDataLookup lookup{ };
    for (const auto& data : teamData) { lookup[data.teamName] = data; }
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
