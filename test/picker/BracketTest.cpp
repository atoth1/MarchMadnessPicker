#include <memory>
#include <string>

#include "catch2/catch_test_macros.hpp"
#include "fmt/core.h"

#include "Bracket.hpp"
#include "BracketData.hpp"
#include "TestUtils.hpp"

TEST_CASE("Bracket - test Matchup", "[Bracket]")// NOLINT
{
  auto strategy = std::make_shared<LexicographicCompareStrategy>( );
  auto matchup1 = std::make_shared<picker::Matchup>("A", "B", strategy);
  CHECK(matchup1->getWinner( ) == "A");// NOLINT

  auto matchup2 = std::make_shared<picker::Matchup>("D", "B", strategy);
  auto matchup3 = std::make_shared<picker::Matchup>("C", "A", strategy);
  auto matchup4 = std::make_shared<picker::Matchup>(matchup2, matchup3, strategy);
  // Do matchup4 first to test recursive behavior
  CHECK(matchup4->getWinner( ) == "A");// NOLINT
  CHECK(matchup2->getWinner( ) == "B");// NOLINT
  CHECK(matchup3->getWinner( ) == "A");// NOLINT
}

namespace {
// NOLINTBEGIN
void checkRegionWinners(const std::unique_ptr<picker::Region>& region, const char suffix)
{
  CHECK(region->roundOf64[0]->getWinner( ) == fmt::format("A{}", suffix));// 1 - 16
  CHECK(region->roundOf64[1]->getWinner( ) == fmt::format("H{}", suffix));// 8 - 9
  CHECK(region->roundOf64[2]->getWinner( ) == fmt::format("E{}", suffix));// 5 - 12
  CHECK(region->roundOf64[3]->getWinner( ) == fmt::format("D{}", suffix));// 4 - 13
  CHECK(region->roundOf64[4]->getWinner( ) == fmt::format("F{}", suffix));// 6 - 11
  CHECK(region->roundOf64[5]->getWinner( ) == fmt::format("C{}", suffix));// 3 - 14
  CHECK(region->roundOf64[6]->getWinner( ) == fmt::format("G{}", suffix));// 7 - 10
  CHECK(region->roundOf64[7]->getWinner( ) == fmt::format("B{}", suffix));// 2 - 15

  CHECK(region->roundOf32[0]->getWinner( ) == fmt::format("A{}", suffix));
  CHECK(region->roundOf32[1]->getWinner( ) == fmt::format("D{}", suffix));
  CHECK(region->roundOf32[2]->getWinner( ) == fmt::format("C{}", suffix));
  CHECK(region->roundOf32[3]->getWinner( ) == fmt::format("B{}", suffix));

  CHECK(region->sweet16[0]->getWinner( ) == fmt::format("A{}", suffix));
  CHECK(region->sweet16[1]->getWinner( ) == fmt::format("B{}", suffix));

  CHECK(region->elite8->getWinner( ) == fmt::format("A{}", suffix));
}
// NOLINTEND

}// namespace

TEST_CASE("Bracket - test makeBracket", "[Bracket]")// NOLINT
{
  auto strategy = std::make_shared<LexicographicCompareStrategy>( );
  const auto bracket = picker::makeBracket(getTestBracketData( ), strategy);

  CHECK(bracket.topLeft->name == "Region 1");// NOLINT
  CHECK(bracket.bottomLeft->name == "Region 2");// NOLINT
  CHECK(bracket.topRight->name == "Region 3");// NOLINT
  CHECK(bracket.bottomRight->name == "Region 4");// NOLINT

  checkRegionWinners(bracket.topLeft, '1');
  checkRegionWinners(bracket.bottomLeft, '2');
  checkRegionWinners(bracket.topRight, '3');
  checkRegionWinners(bracket.bottomRight, '4');
  CHECK(bracket.leftSemifinal->getWinner( ) == "A1");// NOLINT
  CHECK(bracket.rightSemifinal->getWinner( ) == "A3");// NOLINT
  CHECK(bracket.championship->getWinner( ) == "A1");// NOLINT
}