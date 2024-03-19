#include <fstream>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

#include "ProblemData.hpp"
#include "TeamData.hpp"

void picker::ProblemData::validate( ) const {}

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
