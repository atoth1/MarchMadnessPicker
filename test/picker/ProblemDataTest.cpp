#include <fstream>
#include <iterator>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "catch2/catch_test_macros.hpp"
#include "fmt/core.h"
#include "nlohmann/json.hpp"

#include "BracketData.hpp"
#include "ProblemData.hpp"
#include "TeamData.hpp"

namespace {

std::string getBracketDataString( )
{
  return R"({
      "top_left": {
        "teams": [
          { "name": "Alabama", "seed": 1 },
          { "name": "Texas A&M Corpus Chris", "seed": 16 },
          { "name": "Maryland", "seed": 8 },
          { "name": "West Virginia", "seed": 9 },
          { "name": "San Diego St.", "seed": 5 },
          { "name": "Charleston", "seed": 12 },
          { "name": "Virginia", "seed": 4 },
          { "name": "Furman", "seed": 13 },
          { "name": "Creighton", "seed": 6 },
          { "name": "N.C. State", "seed": 11 },
          { "name": "Baylor", "seed": 3 },
          { "name": "UC Santa Barbara", "seed": 14 },
          { "name": "Missouri", "seed": 7 },
          { "name": "Utah St.", "seed": 10 },
          { "name": "Arizona", "seed": 2 },
          { "name": "Princeton", "seed": 15 }
        ]
      },
      "bottom_left": {
        "teams": [
          { "name": "Purdue", "seed": 1 },
          { "name": "Fairleigh Dickinson", "seed": 16 },
          { "name": "Memphis", "seed": 8 },
          { "name": "Florida Atlantic", "seed": 9 },
          { "name": "Duke", "seed": 5 },
          { "name": "Oral Roberts", "seed": 12 },
          { "name": "Tennessee", "seed": 4 },
          { "name": "Louisiana", "seed": 13 },
          { "name": "Kentucky", "seed": 6 },
          { "name": "Providence", "seed": 11 },
          { "name": "Kansas St.", "seed": 3 },
          { "name": "Montana St.", "seed": 14 },
          { "name": "Michigan St.", "seed": 7 },
          { "name": "USC", "seed": 10 },
          { "name": "Marquette", "seed": 2 },
          { "name": "Vermont", "seed": 15 }
        ]
      },
      "top_right": {
        "teams": [
          { "name": "Houston", "seed": 1 },
          { "name": "Northern Kentucky", "seed": 16 },
          { "name": "Iowa", "seed": 8 },
          { "name": "Auburn", "seed": 9 },
          { "name": "Miami FL", "seed": 5 },
          { "name": "Drake", "seed": 12 },
          { "name": "Indiana", "seed": 4 },
          { "name": "Kent St.", "seed": 13 },
          { "name": "Iowa St.", "seed": 6 },
          { "name": "Pittsburgh", "seed": 11 },
          { "name": "Xavier", "seed": 3 },
          { "name": "Kennesaw St.", "seed": 14 },
          { "name": "Texas A&M", "seed": 7 },
          { "name": "Penn St.", "seed": 10 },
          { "name": "Texas", "seed": 2 },
          { "name": "Colgate", "seed": 15 }
        ]
      },
      "bottom_right": {
        "teams": [
          { "name": "Kansas", "seed": 1 },
          { "name": "Howard", "seed": 16 },
          { "name": "Arkansas", "seed": 8 },
          { "name": "Illinois", "seed": 9 },
          { "name": "Saint Mary's", "seed": 5 },
          { "name": "VCU", "seed": 12 },
          { "name": "Connecticut", "seed": 4 },
          { "name": "Iona", "seed": 13 },
          { "name": "TCU", "seed": 6 },
          { "name": "Arizona St.", "seed": 11 },
          { "name": "Gonzaga", "seed": 3 },
          { "name": "Grand Canyon", "seed": 14 },
          { "name": "Northwestern", "seed": 7 },
          { "name": "Boise St.", "seed": 10 },
          { "name": "UCLA", "seed": 2 },
          { "name": "UNC Asheville", "seed": 15 }
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
      "selection_strategy_params": {{ }},
      "randomization_strategy": "std-rand",
      "randomization_strategy_params": {{ }},
      "output_strategy": "file",
      "output_strategy_params": {{ }}
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
  const auto jsonData = nlohmann::json::parse(getBracketDataString( ));
  jsonData.get_to(data);
  return data;
}

picker::ProblemData::TeamDataLookup getExpectedTeamDataLookup( )
{
  std::ifstream teamDataStream("test-team-data.json");
  const auto teamData = nlohmann::json::parse(teamDataStream);
  const auto parsedTeamData = teamData.template get<std::vector<picker::TeamData>>( );

  picker::ProblemData::TeamDataLookup lookup{ };
  for (const auto& data : parsedTeamData) { lookup[data.teamName] = data; }
  return lookup;
}

picker::ProblemData getExpectedProblemDataNoDefaultArgs( )
{
  using namespace nlohmann::literals;
  return { getExpectedBracketData( ),
    getExpectedTeamDataLookup( ),
    "coin-flip",
    "{}"_json,
    "std-rand",
    "{}"_json,
    "file",
    "{}"_json };
}

picker::ProblemData getExpectedProblemDataDefaultArgs( )
{
  return { getExpectedBracketData( ),
    getExpectedTeamDataLookup( ),
    "spread-based",
    std::nullopt,
    "mersenne-twister",
    std::nullopt,
    "stdout",
    std::nullopt };
}

std::vector<std::string> getInvalidInputStrings( )
{
  return { R"({ "team_data_file": "test-team-data.json" })",
    fmt::format(R"({{ "bracket_data": {} }})", getBracketDataString( )) };
}

}// namespace

TEST_CASE("ProblemData parsing - successul parse no default arguments", "[ProblemData]")// NOLINT
{
  const auto jsonData = nlohmann::json::parse(getValidInputStringNoDefaultArgs( ));
  picker::ProblemData problemData{ };
  jsonData.get_to(problemData);
  CHECK(problemData == getExpectedProblemDataNoDefaultArgs( ));// NOLINT
  CHECK_NOTHROW(problemData.validate( ));// NOLINT;
}

TEST_CASE("ProblemData parsing - successul parse with default arguments", "[ProblemData]")// NOLINT
{
  const auto jsonData = nlohmann::json::parse(getValidInputStringDefaultArgs( ));
  picker::ProblemData problemData{ };
  jsonData.get_to(problemData);
  CHECK(problemData == getExpectedProblemDataDefaultArgs( ));// NOLINT
  CHECK_NOTHROW(problemData.validate( ));// NOLINT;
}

TEST_CASE("ProblemData parsing - expected exceptions", "[ProblemData]")// NOLINT
{
  for (const auto& inputString : getInvalidInputStrings( )) {
    const auto jsonData = nlohmann::json::parse(inputString);
    CHECK_THROWS_AS(jsonData.template get<picker::ProblemData>( ), nlohmann::json::exception);// NOLINT
  }
}

TEST_CASE("PriblemData validation - invalid bracket", "[ProblemData]")// NOLINT
{
  const auto jsonData = nlohmann::json::parse(getValidInputStringDefaultArgs( ));
  picker::ProblemData problemData{ };
  jsonData.get_to(problemData);
  picker::TeamData& topSeed = problemData.teamDataLookup.at(*problemData.bracketData.topLeft.teams.begin( ));
  picker::TeamData& bottomSeed =
    problemData.teamDataLookup.at(*std::prev(problemData.bracketData.topLeft.teams.end( )));
  std::swap(topSeed.seed, bottomSeed.seed);
  CHECK_THROWS_AS(problemData.validate( ), std::runtime_error);// NOLINT
}