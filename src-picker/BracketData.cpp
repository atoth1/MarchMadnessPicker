#include <set>
#include <stdexcept>

#include "nlohmann/json.hpp"

#include "BracketData.hpp"

void picker::from_json(const nlohmann::json& input, picker::RegionData& output)// NOLINT(misc-include-cleaner)
{
  if (input.contains("name")) { input.at("name").get_to(output.name); }

  const auto& teams = input.at("teams");
  if (!teams.is_array( )) { throw std::runtime_error("ERROR - Teams must be parsed from a JSON array."); }

  if (teams.size( ) < RegionData::N_TEAMS) { throw std::runtime_error("ERROR - Too few teams in region."); }

  std::set<unsigned> seeds{ };
  for (const auto& team : teams) {
    const auto seed = team.at("seed").template get<unsigned>( );
    seeds.insert(seed);
    team.at("name").get_to(output.teams.at(seed - 1));
  }

  if (seeds.size( ) < RegionData::N_TEAMS) { throw std::runtime_error("ERROR - Duplicate seeds in region."); }
}

void picker::from_json(const nlohmann::json& input, picker::BracketData& output)// NOLINT(misc-include-cleaner)
{
  input.at("top_left").get_to(output.topLeft);
  input.at("bottom_left").get_to(output.bottomLeft);
  input.at("top_right").get_to(output.topRight);
  input.at("bottom_right").get_to(output.bottomRight);
}