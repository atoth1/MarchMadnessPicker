#include <memory>

#include "catch2/catch_test_macros.hpp"

#include "ProblemData.hpp"
#include "SelectionStrategy_CoinFlip.hpp"
#include "SelectionStrategy_RankDeterministic.hpp"
#include "SelectionStrategy_SpreadBased.hpp"
#include "TeamData.hpp"
#include "TestUtils.hpp"

namespace {
// NOLINTBEGIN
picker::ProblemData::TeamDataLookup getTeamDataLookup( )
{
  // adjTempo member is initialized to 100.0 to simplify spread-based calculations
  return { { "A", { "A", 1, 1, 0.0, 0.0, 0.0, 100.0, 0.0, 0.0, 0.0, 0.0, 0.0 } },
    { "B", { "B", 2, 2, 0.0, 0.0, 0.0, 100.0, 0.0, 0.0, 0.0, 0.0, 0.0 } } };
}
// NOLINTEND

}// namespace

TEST_CASE("SelectionStrategy - coin flip", "[SelectionStrategy]")// NOLINT
{
  const auto teamDataLookup = getTeamDataLookup( );

  constexpr double A_WIN_PROB = 0.49;
  picker::CoinFlipStrategy strategy1(std::make_unique<DeterministicStrategy>(A_WIN_PROB));
  CHECK(strategy1.selectWinner("A", "B") == "A");// NOLINT

  constexpr double B_WIN_PROB = 0.51;
  picker::CoinFlipStrategy strategy2(std::make_unique<DeterministicStrategy>(B_WIN_PROB));
  CHECK(strategy2.selectWinner("A", "B") == "B");// NOLINT
}

TEST_CASE("SelectionStrategy - rank deterministic", "[SelectionStrategy]")// NOLINT
{
  const auto teamDataLookup = getTeamDataLookup( );
  picker::RankDeterministicStrategy strategy(&teamDataLookup);
  CHECK(strategy.selectWinner("A", "B") == "A");// NOLINT
}

namespace {
// NOLINTNEXTLINE
void testExpectedSpread(const double spread, const double expectedWinProb, picker::ProblemData::TeamDataLookup& lookup)
{
  lookup.at("A").adjEff = lookup.at("B").adjEff + spread;

  constexpr double probDelta = 1.0e-8;
  picker::SpreadBasedStrategy strategy1(std::make_unique<DeterministicStrategy>(expectedWinProb - probDelta), &lookup);
  CHECK(strategy1.selectWinner("A", "B") == "A");// NOLINT

  picker::SpreadBasedStrategy strategy2(std::make_unique<DeterministicStrategy>(expectedWinProb + probDelta), &lookup);
  CHECK(strategy2.selectWinner("A", "B") == "B");// NOLINT
}
}// namespace

TEST_CASE("SelectionStrategy - spread based", "[SelectionStrategy]")// NOLINT
{
  auto teamDataLookup = getTeamDataLookup( );
  // NOLINTBEGIN
  testExpectedSpread(0.0, 0.5, teamDataLookup);
  testExpectedSpread(1.0, 0.5193, teamDataLookup);
  testExpectedSpread(2.0, 0.5556, teamDataLookup);
  testExpectedSpread(3.0, 0.6147, teamDataLookup);
  testExpectedSpread(4.0, 0.6388, teamDataLookup);
  testExpectedSpread(5.0, 0.6754, teamDataLookup);
  testExpectedSpread(6.0, 0.7151, teamDataLookup);
  testExpectedSpread(7.0, 0.7506, teamDataLookup);
  testExpectedSpread(8.0, 0.7694, teamDataLookup);
  testExpectedSpread(9.0, 0.8078, teamDataLookup);
  testExpectedSpread(10.0, 0.8316, teamDataLookup);
  testExpectedSpread(11.0, 0.8671, teamDataLookup);
  testExpectedSpread(12.0, 0.8792, teamDataLookup);
  testExpectedSpread(13.0, 0.8872, teamDataLookup);
  testExpectedSpread(14.0, 0.9203, teamDataLookup);
  testExpectedSpread(15.0, 0.9454, teamDataLookup);
  testExpectedSpread(16.0, 0.9658, teamDataLookup);
  testExpectedSpread(17.0, 0.9479, teamDataLookup);
  testExpectedSpread(18.0, 0.9677, teamDataLookup);
  testExpectedSpread(19.0, 0.9833, teamDataLookup);
  testExpectedSpread(20.0, 0.9788, teamDataLookup);
  testExpectedSpread(21.0, 0.9727, teamDataLookup);
  testExpectedSpread(22.0, 0.9786, teamDataLookup);
  testExpectedSpread(23.0, 0.9919, teamDataLookup);
  testExpectedSpread(24.0, 0.9999, teamDataLookup);
  //  NOLINTEND
}