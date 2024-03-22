#include <optional>
#include <string>
#include <vector>

#include "catch2/catch_test_macros.hpp"
#include "nlohmann/json.hpp"

#include "TeamData.hpp"

namespace {

std::string getValidInputString( )
{
  return R"(
  [
    {
      "team_name": "Houston",
      "seed": 1,
      "rank": 1,
      "adj_eff": 32.81,
      "adj_off": 121.0,
      "adj_def": 88.2,
      "adj_tempo": 63.5,
      "luck": 0.034,
      "adj_eff_sos": 10.65,
      "adj_off_sos": 111.8,
      "adj_def_sos": 101.2,
      "adj_eff_sos_nc": -0.61
    },
    {
      "team_name": "Connecticut",
      "seed": null,
      "rank": 2,
      "adj_eff": 31.17,
      "adj_off": 126.1,
      "adj_def": 94.9,
      "adj_tempo": 64.5,
      "luck": 0.045,
      "adj_eff_sos": 9.4,
      "adj_off_sos": 111.4,
      "adj_def_sos": 102.0,
      "adj_eff_sos_nc": -3.25
    }
  ])";
}

std::vector<picker::TeamData> getExpectedTeamData( )
{
  // NOLINTBEGIN(*-magic-numbers)
  return { { "Houston", 1, 1, 32.81, 121.0, 88.2, 63.5, 0.034, 10.65, 111.8, 101.2, -0.61 },
    { "Connecticut", std::nullopt, 2, 31.17, 126.1, 94.9, 64.5, 0.045, 9.4, 111.4, 102.0, -3.25 } };
  // NOLINTEND(*-magic-numbers)
}

std::vector<std::string> getInvalidInputStrings( )
{
  return {
    R"({
      "seed": 1,
      "rank": 1,
      "adj_eff": 32.81,
      "adj_off": 121.0,
      "adj_def": 88.2,
      "adj_tempo": 63.5,
      "luck": 0.034,
      "adj_eff_sos": 10.65,
      "adj_off_sos": 111.8,
      "adj_def_sos": 101.2,
      "adj_eff_sos_nc": -0.61
    })",
    R"({
      "team_name": "Houston",
      "rank": 1,
      "adj_eff": 32.81,
      "adj_off": 121.0,
      "adj_def": 88.2,
      "adj_tempo": 63.5,
      "luck": 0.034,
      "adj_eff_sos": 10.65,
      "adj_off_sos": 111.8,
      "adj_def_sos": 101.2,
      "adj_eff_sos_nc": -0.61
    })",
    R"({
      "team_name": "Houston",
      "seed": 1,
      "adj_eff": 32.81,
      "adj_off": 121.0,
      "adj_def": 88.2,
      "adj_tempo": 63.5,
      "luck": 0.034,
      "adj_eff_sos": 10.65,
      "adj_off_sos": 111.8,
      "adj_def_sos": 101.2,
      "adj_eff_sos_nc": -0.61
    })",
    R"({
      "team_name": "Houston",
      "rank": 1,
      "seed": null,
      "adj_off": 121.0,
      "adj_def": 88.2,
      "adj_tempo": 63.5,
      "luck": 0.034,
      "adj_eff_sos": 10.65,
      "adj_off_sos": 111.8,
      "adj_def_sos": 101.2,
      "adj_eff_sos_nc": -0.61
    })",
    R"({
      "team_name": 42,
      "seed": 1,
      "rank": 1,
      "adj_eff": 32.81,
      "adj_off": 121.0,
      "adj_def": 88.2,
      "adj_tempo": 63.5,
      "luck": 0.034,
      "adj_eff_sos": 10.65,
      "adj_off_sos": 111.8,
      "adj_def_sos": 101.2,
      "adj_eff_sos_nc": -0.61
    })",
    R"({
      "team_name": "Houston",
      "seed": "One",
      "rank": 1,
      "adj_eff": 32.81,
      "adj_off": 121.0,
      "adj_def": 88.2,
      "adj_tempo": 63.5,
      "luck": 0.034,
      "adj_eff_sos": 10.65,
      "adj_off_sos": 111.8,
      "adj_def_sos": 101.2,
      "adj_eff_sos_nc": -0.61
    })",
    R"({
      "team_name": "Houston",
      "seed": 1,
      "rank": "two",
      "adj_eff": 32.81,
      "adj_off": 121.0,
      "adj_def": 88.2,
      "adj_tempo": 63.5,
      "luck": 0.034,
      "adj_eff_sos": 10.65,
      "adj_off_sos": 111.8,
      "adj_def_sos": 101.2,
      "adj_eff_sos_nc": -0.61
    })"
  };
}
}// namespace

TEST_CASE("TeamData parsing - successful parse", "[TeamData]")// NOLINT(misc-use-anonymous-namespace)
{
  const auto jsonData = nlohmann::json::parse(getValidInputString( ));// NOLINT(misc-include-cleaner)
  std::vector<picker::TeamData> teamData{ };
  jsonData.get_to(teamData);

  const auto expected = getExpectedTeamData( );
  // NOLINTBEGIN(cppcoreguidelines-avoid-do-while)
  REQUIRE(teamData.size( ) == 2);
  CHECK(teamData[0] == expected[0]);
  CHECK(teamData[1] == expected[1]);
  // NOLINTEND(cppcoreguidelines-avoid-do-while)
}

TEST_CASE("TeamData parsing - expected exceptions", "[TeamData]")// NOLINT(misc-use-anonymous-namespace)
{
  for (const auto& inputString : getInvalidInputStrings( )) {
    const auto jsonData = nlohmann::json::parse(inputString);// NOLINT(misc-include-cleaner)
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while, misc-include-cleaner)
    CHECK_THROWS_AS(jsonData.template get<picker::TeamData>( ), nlohmann::json::exception);
  }
}
