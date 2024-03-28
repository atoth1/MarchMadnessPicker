#include <set>
#include <stdexcept>
#include <string_view>

#include "fmt/core.h"
#include "fmt/ranges.h"// NOLINT(misc-inlcude-cleaner)
#include "nlohmann/json.hpp"

#include "BracketData.hpp"
#include "LogManager.hpp"

void picker::from_json(const nlohmann::json& input, picker::RegionData& output)// NOLINT(misc-include-cleaner)
{
  if (input.contains("name")) { input.at("name").get_to(output.name); }

  const auto& teams = input.at("teams");
  if (!teams.is_array( )) { throw std::runtime_error("ERROR - Teams must be parsed from a JSON array."); }

  if (teams.size( ) < RegionData::N_TEAMS) {
    logError(fmt::format("There are only {} teams in the region.", teams.size( )));
    throw std::runtime_error("ERROR - Too few teams in region.");
  }

  std::set<unsigned> seeds{ };
  for (const auto& team : teams) {
    const auto seed = team.at("seed").template get<unsigned>( );
    seeds.insert(seed);
    team.at("name").get_to(output.teams.at(seed - 1));
  }

  if (seeds.size( ) < RegionData::N_TEAMS) {
    logError(fmt::format("Parsed team seeds {} (should be 1 through 16).", seeds));
    throw std::runtime_error("ERROR - Duplicate seeds in region.");
  }

  logDebug(fmt::format("Parsed seed-ordered team names: {}", output.teams));
}

void picker::from_json(const nlohmann::json& input, picker::BracketData& output)// NOLINT(misc-include-cleaner)
{
  auto parseRegion = [&](std::string_view name, picker::RegionData& regionData) {
    try {
      logDebug(fmt::format("Parsing region {}.", name));
      input.at(name).get_to(regionData);
    } catch (...) {
      logError("Failed to parse region data.");
      throw;
    }
  };
  parseRegion("top_left", output.topLeft);
  parseRegion("bottom_left", output.bottomLeft);
  parseRegion("top_right", output.topRight);
  parseRegion("bottom_right", output.bottomRight);
}