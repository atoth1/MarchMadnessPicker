#include <fstream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "catch2/catch_test_macros.hpp"
#include "fmt/core.h"
#include "nlohmann/json.hpp"

#include "BracketData.hpp"
#include "Constants.hpp"
#include "ProblemData.hpp"
#include "TeamData.hpp"

namespace {

std::string getBracketDataString( )
{
  return R"({
      "top_left": {
        "teams": [
          { "name": "A1", "seed": 1 },
          { "name": "B1", "seed": 2 },
          { "name": "C1", "seed": 3 },
          { "name": "D1", "seed": 4 },
          { "name": "E1", "seed": 5 },
          { "name": "F1", "seed": 6 },
          { "name": "G1", "seed": 7 },
          { "name": "H1", "seed": 8 },
          { "name": "I1", "seed": 9 },
          { "name": "J1", "seed": 10 },
          { "name": "K1", "seed": 11 },
          { "name": "L1", "seed": 12 },
          { "name": "M1", "seed": 13 },
          { "name": "N1", "seed": 14 },
          { "name": "O1", "seed": 15 },
          { "name": "P1", "seed": 16 }
        ]
      },
      "bottom_left": {
        "teams": [
          { "name": "A2", "seed": 1 },
          { "name": "B2", "seed": 2 },
          { "name": "C2", "seed": 3 },
          { "name": "D2", "seed": 4 },
          { "name": "E2", "seed": 5 },
          { "name": "F2", "seed": 6 },
          { "name": "G2", "seed": 7 },
          { "name": "H2", "seed": 8 },
          { "name": "I2", "seed": 9 },
          { "name": "J2", "seed": 10 },
          { "name": "K2", "seed": 11 },
          { "name": "L2", "seed": 12 },
          { "name": "M2", "seed": 13 },
          { "name": "N2", "seed": 14 },
          { "name": "O2", "seed": 15 },
          { "name": "P2", "seed": 16 }
        ]
      },
      "top_right": {
        "teams": [
          { "name": "A3", "seed": 1 },
          { "name": "B3", "seed": 2 },
          { "name": "C3", "seed": 3 },
          { "name": "D3", "seed": 4 },
          { "name": "E3", "seed": 5 },
          { "name": "F3", "seed": 6 },
          { "name": "G3", "seed": 7 },
          { "name": "H3", "seed": 8 },
          { "name": "I3", "seed": 9 },
          { "name": "J3", "seed": 10 },
          { "name": "K3", "seed": 11 },
          { "name": "L3", "seed": 12 },
          { "name": "M3", "seed": 13 },
          { "name": "N3", "seed": 14 },
          { "name": "O3", "seed": 15 },
          { "name": "P3", "seed": 16 }
        ]
      },
      "bottom_right": {
        "teams": [
          { "name": "A4", "seed": 1 },
          { "name": "B4", "seed": 2 },
          { "name": "C4", "seed": 3 },
          { "name": "D4", "seed": 4 },
          { "name": "E4", "seed": 5 },
          { "name": "F4", "seed": 6 },
          { "name": "G4", "seed": 7 },
          { "name": "H4", "seed": 8 },
          { "name": "I4", "seed": 9 },
          { "name": "J4", "seed": 10 },
          { "name": "K4", "seed": 11 },
          { "name": "L4", "seed": 12 },
          { "name": "M4", "seed": 13 },
          { "name": "N4", "seed": 14 },
          { "name": "O4", "seed": 15 },
          { "name": "P4", "seed": 16 }
        ]
      }
    })";
}

std::string getValidInputStringNoDefaultArgs( )
{
  return fmt::format(
    R"({{
      "bracket_data": {},
      "team_data_file": "test-team-data.json",
      "selection_strategy": "coin-flip",
      "selection_strategy_params": {{ "A": "B" }},
      "randomization_strategy": "std-rand",
      "randomization_strategy_params": {{ "C": 1 }},
      "output_strategy": "file",
      "output_strategy_params": {{ "D": "E" }}
    }})",
    getBracketDataString( ));
}

std::string getValidInputStringDefaultArgs( )
{
  return fmt::format(
    R"({{
      "bracket_data": {},
      "team_data_file": "test-team-data.json"
    }})",
    getBracketDataString( ));
}

picker::BracketData getExpectedBracketData( )
{
  picker::BracketData data{ };
  const auto jsonData = nlohmann::json::parse(getBracketDataString( ));// NOLINT(misc-include-cleaner)
  jsonData.get_to(data);
  return data;
}

std::shared_ptr<picker::ProblemData::TeamDataLookup> getExpectedTeamDataLookup( )
{
  std::ifstream teamDataStream("test-team-data.json");
  const auto teamData = nlohmann::json::parse(teamDataStream);// NOLINT(misc-include-cleaner)
  const auto parsedTeamData = teamData.template get<std::vector<picker::TeamData>>( );

  auto lookup = std::make_shared<picker::ProblemData::TeamDataLookup>( );
  for (const auto& data : parsedTeamData) { (*lookup)[data.teamName] = data; }
  return lookup;
}

picker::ProblemData getExpectedProblemDataNoDefaultArgs( )
{
  using namespace nlohmann::literals;
  return { getExpectedBracketData( ),
    getExpectedTeamDataLookup( ),
    std::string{ picker::COIN_FLIP_STRATEGY_LABEL },
    R"({ "A": "B" })"_json,
    std::string{ picker::STD_RAND_STRATEGY_LABEL },
    R"({ "C": 1 })"_json,
    std::string{ picker::FILE_OUT_STRATEGY_LABEL },
    R"({ "D": "E" })"_json };
}

picker::ProblemData getExpectedProblemDataDefaultArgs( )
{
  return { getExpectedBracketData( ),
    getExpectedTeamDataLookup( ),
    std::string{ picker::SPREAD_BASED_STRATEGY_LABEL },
    { },
    std::string{ picker::MERSENNE_TWISTER_STRATEGY_LABEL },
    { },
    std::string{ picker::STD_OUT_STRATEGY_LABEL },
    {} };
}

std::vector<std::string> getInvalidInputStrings( )
{
  return { R"({ "team_data_file": "test-team-data.json" })",
    fmt::format(R"({{ "bracket_data": {} }})", getBracketDataString( )) };
}

}// namespace

// NOLINTNEXTLINE(misc-use-anonymous-namespace)
TEST_CASE("ProblemData parsing - successul parse no default arguments", "[ProblemData]")
{
  const auto jsonData = nlohmann::json::parse(getValidInputStringNoDefaultArgs( ));// NOLINT(misc-include-cleaner)
  picker::ProblemData problemData{ };
  jsonData.get_to(problemData);
  CHECK(problemData == getExpectedProblemDataNoDefaultArgs( ));// NOLINT(cppcoreguidelines-avoid-do-while)
  CHECK_NOTHROW(problemData.validate( ));// NOLINT(cppcoreguidelines-avoid-do-while)
}

// NOLINTNEXTLINE(misc-use-anonymous-namespace)
TEST_CASE("ProblemData parsing - successul parse with default arguments", "[ProblemData]")
{
  const auto jsonData = nlohmann::json::parse(getValidInputStringDefaultArgs( ));// NOLINT(misc-include-cleaner)
  picker::ProblemData problemData{ };
  jsonData.get_to(problemData);
  CHECK(problemData == getExpectedProblemDataDefaultArgs( ));// NOLINT(cppcoreguidelines-avoid-do-while)
  CHECK_NOTHROW(problemData.validate( ));// NOLINT(cppcoreguidelines-avoid-do-while)
}

TEST_CASE("ProblemData parsing - expected exceptions", "[ProblemData]")// NOLINT(misc-use-anonymous-namespace)
{
  for (const auto& inputString : getInvalidInputStrings( )) {
    const auto jsonData = nlohmann::json::parse(inputString);// NOLINT(misc-include-cleaner)
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while, misc-include-cleaner)
    CHECK_THROWS_AS(jsonData.template get<picker::ProblemData>( ), nlohmann::json::exception);
  }
}

TEST_CASE("PriblemData validation - invalid bracket", "[ProblemData]")// NOLINT(misc-use-anonymous-namespace)
{
  const auto jsonData = nlohmann::json::parse(getValidInputStringDefaultArgs( ));// NOLINT(misc-include-cleaner)
  picker::ProblemData problemData{ };
  jsonData.get_to(problemData);
  picker::TeamData& topSeed = problemData.teamDataLookup->at(*problemData.bracketData.topLeft.teams.begin( ));
  picker::TeamData& bottomSeed =
    problemData.teamDataLookup->at(*std::prev(problemData.bracketData.topLeft.teams.end( )));
  std::swap(topSeed.seed, bottomSeed.seed);
  CHECK_THROWS_AS(problemData.validate( ), std::runtime_error);// NOLINT(cppcoreguidelines-avoid-do-while)
}
