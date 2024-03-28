#include <algorithm>
#include <cmath>

#include "fmt/core.h"
#include "nlohmann/json.hpp"

#include "LogManager.hpp"
#include "TeamData.hpp"

void picker::from_json(const nlohmann::json& input, picker::TeamData& output)// NOLINT(misc-include-cleaner)
{
  logDebug("Parsing team data.");
  try {
    input.at("team_name").get_to(output.teamName);
    if (!input.at("seed").is_null( )) { output.seed = input.at("seed").template get<int>( ); }
    input.at("rank").get_to(output.rank);
    input.at("adj_eff").get_to(output.adjEff);
    input.at("adj_off").get_to(output.adjOff);
    input.at("adj_def").get_to(output.adjDef);
    input.at("adj_tempo").get_to(output.adjTempo);
    input.at("luck").get_to(output.luck);
    input.at("adj_eff_sos").get_to(output.adjEffSos);
    input.at("adj_off_sos").get_to(output.adjOffSos);
    input.at("adj_def_sos").get_to(output.adjDefSos);
    input.at("adj_eff_sos_nc").get_to(output.adjEffSosNc);
  } catch (...) {
    logError("Failed to parse team data.");
    throw;
  }
  logDebug(fmt::format("Successfully parsed data for team {}.", output.teamName));
}

bool picker::TeamData::operator==(const picker::TeamData& other) const noexcept
{
  auto floatingEqual = [](const double x, const double y) {
    constexpr double absTol = 1.e-14;
    constexpr double relTol = 1.e-14;
    return std::abs(x - y) < absTol + relTol * (std::max(std::abs(x), std::abs(y)));
  };

  return teamName == other.teamName && seed == other.seed && rank == other.rank && floatingEqual(adjEff, other.adjEff)
         && floatingEqual(adjOff, other.adjOff) && floatingEqual(adjDef, other.adjDef)
         && floatingEqual(adjTempo, other.adjTempo) && floatingEqual(luck, other.luck)
         && floatingEqual(adjEffSos, other.adjEffSos) && floatingEqual(adjOffSos, other.adjOffSos)
         && floatingEqual(adjDefSos, other.adjDefSos) && floatingEqual(adjEffSosNc, other.adjEffSosNc);
}