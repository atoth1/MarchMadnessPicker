#include <stdexcept>
#include <string>
#include <vector>

#include "catch2/catch_test_macros.hpp"
#include "fmt/core.h"
#include "nlohmann/json.hpp"

#include "BracketData.hpp"

namespace {
std::string getValidRegionInputString( )
{
  return R"(
    [
      { "name": "A", "seed": 1 },
      { "name": "B", "seed": 2 },
      { "name": "C", "seed": 3 },
      { "name": "D", "seed": 4 },
      { "name": "E", "seed": 5 },
      { "name": "F", "seed": 6 },
      { "name": "G", "seed": 7 },
      { "name": "H", "seed": 8 },
      { "name": "I", "seed": 9 },
      { "name": "J", "seed": 10 },
      { "name": "K", "seed": 11 },
      { "name": "L", "seed": 12 },
      { "name": "M", "seed": 13 },
      { "name": "N", "seed": 14 },
      { "name": "O", "seed": 15 },
      { "name": "P", "seed": 16 }
    ]
  )";
}

picker::RegionData getExpectedRegionData( )
{
  return { { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P" } };
}

std::vector<std::string> getRuntimeErrorRegionInputStrings( )
{
  return { R"({ })",
    R"(
      [
        { "name": "A", "seed": 1 }
      ]
    )",
    R"(
      [
        { "name": "A", "seed": 1 },
        { "name": "B", "seed": 1 },
        { "name": "C", "seed": 3 },
        { "name": "D", "seed": 4 },
        { "name": "E", "seed": 5 },
        { "name": "F", "seed": 6 },
        { "name": "G", "seed": 7 },
        { "name": "H", "seed": 8 },
        { "name": "I", "seed": 9 },
        { "name": "J", "seed": 10 },
        { "name": "K", "seed": 11 },
        { "name": "L", "seed": 12 },
        { "name": "M", "seed": 13 },
        { "name": "N", "seed": 14 },
        { "name": "O", "seed": 15 },
        { "name": "P", "seed": 16 }
      ]
    )" };
}

std::vector<std::string> getJsonErrorRegionInputStrings( )
{
  return {
    R"(
      [
        { "name": "A" },
        { "name": "B", "seed": 2 },
        { "name": "C", "seed": 3 },
        { "name": "D", "seed": 4 },
        { "name": "E", "seed": 5 },
        { "name": "F", "seed": 6 },
        { "name": "G", "seed": 7 },
        { "name": "H", "seed": 8 },
        { "name": "I", "seed": 9 },
        { "name": "J", "seed": 10 },
        { "name": "K", "seed": 11 },
        { "name": "L", "seed": 12 },
        { "name": "M", "seed": 13 },
        { "name": "N", "seed": 14 },
        { "name": "O", "seed": 15 },
        { "name": "P", "seed": 16 }
      ]
    )",
    R"(
      [
        { "seed": 1 },
        { "name": "B", "seed": 2 },
        { "name": "C", "seed": 3 },
        { "name": "D", "seed": 4 },
        { "name": "E", "seed": 5 },
        { "name": "F", "seed": 6 },
        { "name": "G", "seed": 7 },
        { "name": "H", "seed": 8 },
        { "name": "I", "seed": 9 },
        { "name": "J", "seed": 10 },
        { "name": "K", "seed": 11 },
        { "name": "L", "seed": 12 },
        { "name": "M", "seed": 13 },
        { "name": "N", "seed": 14 },
        { "name": "O", "seed": 15 },
        { "name": "P", "seed": 16 }
      ]
    )"
  };
}

std::string getValidBracketInputString( )
{
  return fmt::format(R"({{ "top_left": {}, "bottom_left": {}, "top_right": {}, "bottom_right": {} }})",
    getValidRegionInputString( ),
    getValidRegionInputString( ),
    getValidRegionInputString( ),
    getValidRegionInputString( ));
}

picker::BracketData getExpectedBracketData( )
{
  return { getExpectedRegionData( ), getExpectedRegionData( ), getExpectedRegionData( ), getExpectedRegionData( ) };
}

std::vector<std::string> getInvalidBracketInputStrings( )
{
  // Come back to this - figure out passing format string to fmt::format call in a lambda.
  return { fmt::format(R"({{ "bottom_left": {}, "top_right": {}, "bottom_right": {} }})",
             getValidRegionInputString( ),
             getValidRegionInputString( ),
             getValidRegionInputString( )),
    fmt::format(R"({{ "top_left": {}, "top_right": {}, "bottom_right": {} }})",
      getValidRegionInputString( ),
      getValidRegionInputString( ),
      getValidRegionInputString( )),
    fmt::format(R"({{ "top_left": {}, "bottom_left": {}, "bottom_right": {} }})",
      getValidRegionInputString( ),
      getValidRegionInputString( ),
      getValidRegionInputString( )),
    fmt::format(R"({{ "top_left": {}, "bottom_left": {}, "top_right": {} }})",
      getValidRegionInputString( ),
      getValidRegionInputString( ),
      getValidRegionInputString( )) };
}

}// namespace

TEST_CASE("RegionData parsing - successul parse", "[RegionData]")// NOLINT
{
  const auto jsonData = nlohmann::json::parse(getValidRegionInputString( ));
  picker::RegionData regionData{ };
  jsonData.get_to(regionData);
  CHECK(regionData == getExpectedRegionData( ));// NOLINT
}

TEST_CASE("RegionData parsing - expected exceptions", "[RegionData]")// NOLINT
{
  for (const auto& inputString : getRuntimeErrorRegionInputStrings( )) {
    const auto jsonData = nlohmann::json::parse(inputString);
    REQUIRE_THROWS_AS(jsonData.template get<picker::RegionData>( ), std::runtime_error);// NOLINT
  }

  for (const auto& inputString : getJsonErrorRegionInputStrings( )) {
    const auto jsonData = nlohmann::json::parse(inputString);
    REQUIRE_THROWS_AS(jsonData.template get<picker::RegionData>( ), nlohmann::json::exception);// NOLINT
  }
}

TEST_CASE("BracketData parsing - successul parse", "[BracketData]")// NOLINT
{
  const auto jsonData = nlohmann::json::parse(getValidBracketInputString( ));
  picker::BracketData bracketData{ };
  jsonData.get_to(bracketData);
  CHECK(bracketData == getExpectedBracketData( ));// NOLINT
}

TEST_CASE("BracketData parsing - expected exceptions", "[BracketData]")// NOLINT
{
  for (const auto& inputString : getInvalidBracketInputStrings( )) {
    const auto jsonData = nlohmann::json::parse(inputString);
    REQUIRE_THROWS_AS(jsonData.template get<picker::BracketData>( ), nlohmann::json::exception);// NOLINT
  }
}
