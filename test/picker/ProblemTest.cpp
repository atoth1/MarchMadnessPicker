#include <algorithm>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "catch2/catch_test_macros.hpp"

#include "Constants.hpp"
#include "Problem.hpp"
#include "TestUtils.hpp"

TEST_CASE("Problem - run without setup", "[Problem]")// NOLINT(misc-use-anonymous-namespace)
{
  const std::string inFile{ "test-input.json" };
  picker::Problem problem{ inFile };

  constexpr std::string_view deterministicStrategyLabel{ "deterministic" };
  problem.registerRandomizationStrategyFactory(
    deterministicStrategyLabel, std::make_unique<DeterministicStrategyFactory>( ));

  constexpr std::string_view lexicographicStrategyLabel{ "lexicographic" };
  problem.registerSelectionStrategyFactory(
    lexicographicStrategyLabel, std::make_unique<LexicographicCompareStrategyFactory>( ));

  constexpr std::string_view stringstreamStrategyLabel{ "stringstream" };
  auto out = std::make_shared<std::ostringstream>( );
  problem.registerOutputStrategyFactory(
    stringstreamStrategyLabel, std::make_unique<StringstreamOutStrategyFactory>(out));

  problem.run( );
  CHECK(out->str( ).empty( ));// NOLINT(cppcoreguidelines-avoid-do-while)
}

TEST_CASE("Problem - run with invalid selection strategy", "[Problem]")// NOLINT(misc-use-anonymous-namespace)
{
  const std::string inFile{ "test-input.json" };
  picker::Problem problem{ inFile };

  constexpr std::string_view deterministicStrategyLabel{ "deterministic" };
  problem.registerRandomizationStrategyFactory(
    deterministicStrategyLabel, std::make_unique<DeterministicStrategyFactory>( ));

  constexpr std::string_view lexicographicStrategyLabel{ "mismatched" };
  problem.registerSelectionStrategyFactory(
    lexicographicStrategyLabel, std::make_unique<LexicographicCompareStrategyFactory>( ));

  constexpr std::string_view stringstreamStrategyLabel{ "stringstream" };
  auto out = std::make_shared<std::ostringstream>( );
  problem.registerOutputStrategyFactory(
    stringstreamStrategyLabel, std::make_unique<StringstreamOutStrategyFactory>(out));

  problem.run( );
  CHECK(out->str( ).empty( ));// NOLINT(cppcoreguidelines-avoid-do-while)
}

TEST_CASE("Problem - run with invalid output strategy", "[Problem]")// NOLINT(misc-use-anonymous-namespace)
{
  const std::string inFile{ "test-input.json" };
  picker::Problem problem{ inFile };

  constexpr std::string_view deterministicStrategyLabel{ "deterministic" };
  problem.registerRandomizationStrategyFactory(
    deterministicStrategyLabel, std::make_unique<DeterministicStrategyFactory>( ));

  constexpr std::string_view lexicographicStrategyLabel{ "lexicographic" };
  problem.registerSelectionStrategyFactory(
    lexicographicStrategyLabel, std::make_unique<LexicographicCompareStrategyFactory>( ));

  constexpr std::string_view stringstreamStrategyLabel{ "mismatched" };
  auto out = std::make_shared<std::ostringstream>( );
  problem.registerOutputStrategyFactory(
    stringstreamStrategyLabel, std::make_unique<StringstreamOutStrategyFactory>(out));

  problem.run( );
  CHECK(out->str( ).empty( ));// NOLINT(cppcoreguidelines-avoid-do-while)
}

TEST_CASE("Problem - setup registers expected strategies", "[Problem]")// NOLINT(misc-use-anonymous-namespace)
{
  const std::string inFile{ "test-input.json" };
  picker::Problem problem{ inFile };

  // NOLINTBEGIN(cppcoreguidelines-avoid-do-while)
  CHECK(problem.getRegisteredOutputStrategyNames( ).empty( ));
  CHECK(problem.getRegisteredRandomizationStrategyNames( ).empty( ));
  CHECK(problem.getRegisteredSelectionStrategyNames( ).empty( ));
  // NOLINTEND(cppcoreguidelines-avoid-do-while)

  problem.setup( );

  auto outputStrategyNames = problem.getRegisteredOutputStrategyNames( );
  auto randomizationStrategyNames = problem.getRegisteredRandomizationStrategyNames( );
  auto selectionStrategyNames = problem.getRegisteredSelectionStrategyNames( );
  std::sort(outputStrategyNames.begin( ), outputStrategyNames.end( ));
  std::sort(randomizationStrategyNames.begin( ), randomizationStrategyNames.end( ));
  std::sort(selectionStrategyNames.begin( ), selectionStrategyNames.end( ));
  // NOLINTBEGIN(cppcoreguidelines-avoid-do-while)
  CHECK(outputStrategyNames == std::vector{ picker::FILE_OUT_STRATEGY_LABEL, picker::STD_OUT_STRATEGY_LABEL });
  CHECK(
    randomizationStrategyNames
    == std::vector{
      picker::MERSENNE_TWISTER_STRATEGY_LABEL, picker::MINSTD_RAND_STRATEGY_LABEL, picker::STD_RAND_STRATEGY_LABEL });
  CHECK(selectionStrategyNames
        == std::vector{ picker::COIN_FLIP_STRATEGY_LABEL,
          picker::RANK_DETERMINISTIC_STRATEGY_LABEL,
          picker::SPREAD_BASED_STRATEGY_LABEL });
  // NOLINTEND(cppcoreguidelines-avoid-do-while)
}

TEST_CASE("Problem - successful simulation", "[Problem]")// NOLINT(misc-use-anonymous-namespace)
{
  const std::string inFile{ "test-input.json" };
  picker::Problem problem{ inFile };

  constexpr std::string_view deterministicStrategyLabel{ "deterministic" };
  problem.registerRandomizationStrategyFactory(
    deterministicStrategyLabel, std::make_unique<DeterministicStrategyFactory>( ));

  constexpr std::string_view lexicographicStrategyLabel{ "lexicographic" };
  problem.registerSelectionStrategyFactory(
    lexicographicStrategyLabel, std::make_unique<LexicographicCompareStrategyFactory>( ));

  constexpr std::string_view stringstreamStrategyLabel{ "stringstream" };
  auto out = std::make_shared<std::ostringstream>( );
  problem.registerOutputStrategyFactory(
    stringstreamStrategyLabel, std::make_unique<StringstreamOutStrategyFactory>(out));

  problem.setup( );
  problem.run( );
  CHECK(out->str( ) == getExpectedOutput( ));// NOLINT(cppcoreguidelines-avoid-do-while)
}
