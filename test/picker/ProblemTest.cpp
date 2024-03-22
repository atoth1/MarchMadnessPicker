#include <memory>
#include <sstream>
#include <string>
#include <string_view>

#include "catch2/catch_test_macros.hpp"

#include "Problem.hpp"
#include "TestUtils.hpp"

TEST_CASE("Problem - successful simulation", "[Problem]")// NOLINT
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
  CHECK(out->str( ) == getExpectedOutput( ));// NOLINT
}
