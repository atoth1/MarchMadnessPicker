#include <memory>
#include <string>//NOLINT(misc-include-cleaner)

#include "catch2/catch_test_macros.hpp"
#include "fmt/core.h"

#include "Bracket.hpp"
#include "BracketData.hpp"//NOLINT(misc-include-cleaner)
#include "TestUtils.hpp"

TEST_CASE("Bracket - test Matchup", "[Bracket]")// NOLINT(misc-use-anonymous-namespace)
{
  auto strategy = std::make_shared<LexicographicCompareStrategy>( );
  auto matchup1 = std::make_shared<picker::Matchup>("A", "B", strategy);
  CHECK(matchup1->getWinner( ) == "A");// NOLINT

  auto matchup2 = std::make_shared<picker::Matchup>("D", "B", strategy);
  auto matchup3 = std::make_shared<picker::Matchup>("C", "A", strategy);
  auto matchup4 = std::make_shared<picker::Matchup>(matchup2, matchup3, strategy);
  // Do matchup4 first to test recursive behavior
  // NOLINTBEGIN(cppcoreguidelines-avoid-do-while)
  CHECK(matchup4->getWinner( ) == "A");
  CHECK(matchup2->getWinner( ) == "B");
  CHECK(matchup3->getWinner( ) == "A");
  // NOLINTEND(cppcoreguidelines-avoid-do-while)
}

namespace {
// NOLINTBEGIN
void checkRegionWinners(const std::unique_ptr<picker::Region>& region, const char suffix)
{
  CHECK(region->roundOf64[0]->getWinner( ) == fmt::format("A{}", suffix));
  CHECK(region->roundOf64[1]->getWinner( ) == fmt::format("H{}", suffix));
  CHECK(region->roundOf64[2]->getWinner( ) == fmt::format("E{}", suffix));
  CHECK(region->roundOf64[3]->getWinner( ) == fmt::format("D{}", suffix));
  CHECK(region->roundOf64[4]->getWinner( ) == fmt::format("F{}", suffix));
  CHECK(region->roundOf64[5]->getWinner( ) == fmt::format("C{}", suffix));
  CHECK(region->roundOf64[6]->getWinner( ) == fmt::format("G{}", suffix));
  CHECK(region->roundOf64[7]->getWinner( ) == fmt::format("B{}", suffix));

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

// NOLINTNEXTLINE(misc-use-anonymous-namespace, readability-function-cognitive-complexity)
TEST_CASE("Bracket - test makeBracket", "[Bracket]")
{
  auto strategy = std::make_shared<LexicographicCompareStrategy>( );
  const auto bracket = picker::makeBracket(getTestBracketData( ), strategy);

  // NOLINTBEGIN(cppcoreguidelines-avoid-do-while)
  CHECK(bracket.topLeft->name == "Region 1");
  CHECK(bracket.bottomLeft->name == "Region 2");
  CHECK(bracket.topRight->name == "Region 3");
  CHECK(bracket.bottomRight->name == "Region 4");
  // NOLINTEND(cppcoreguidelines-avoid-do-while)

  checkRegionWinners(bracket.topLeft, '1');
  checkRegionWinners(bracket.bottomLeft, '2');
  checkRegionWinners(bracket.topRight, '3');
  checkRegionWinners(bracket.bottomRight, '4');

  // NOLINTBEGIN(cppcoreguidelines-avoid-do-while)
  CHECK(bracket.leftSemifinal->getWinner( ) == "A1");
  CHECK(bracket.rightSemifinal->getWinner( ) == "A3");
  CHECK(bracket.championship->getWinner( ) == "A1");
  // NOLINTEND(cppcoreguidelines-avoid-do-while)
}