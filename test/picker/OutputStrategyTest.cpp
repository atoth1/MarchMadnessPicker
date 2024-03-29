#include <fstream>
#include <memory>
#include <sstream>
#include <string>

#include "catch2/catch_test_macros.hpp"

#include "Bracket.hpp"
#include "OutputStrategy_FileOut.hpp"
#include "OutputStrategy_StdOut.hpp"
#include "TestUtils.hpp"

TEST_CASE("OutputStrategy - file output creates file", "[OutputStrategy]")// NOLINT(misc-use-anonymous-namespace)
{
  const auto selectionStrategy = std::make_shared<LexicographicCompareStrategy>( );
  const auto bracket = picker::makeBracket(getTestBracketData( ), selectionStrategy);

  const std::string fileName{ "test-output.txt" };
  const picker::FileOutStrategy outputStrategy{ fileName };
  outputStrategy.writeOutput(bracket);

  const std::ifstream outFile{ fileName };
  CHECK(outFile.is_open( ));// NOLINT(cppcoreguidelines-avoid-do-while)
}

TEST_CASE("OutputStrategy - print to stdout", "[OutputStrategy]")// NOLINT(misc-use-anonymous-namespace)
{
  const auto selectionStrategy = std::make_shared<LexicographicCompareStrategy>( );
  const auto bracket = picker::makeBracket(getTestBracketData( ), selectionStrategy);

  const picker::StdOutStrategy outputStrategy{ };
  outputStrategy.writeOutput(bracket);
}

TEST_CASE("OutputStrategy - expected output", "[OutputStrategy]")// NOLINT(misc-use-anonymous-namespace)
{
  const auto selectionStrategy = std::make_shared<LexicographicCompareStrategy>( );
  const auto bracket = picker::makeBracket(getTestBracketData( ), selectionStrategy);

  auto out = std::make_shared<std::ostringstream>( );
  const StringstreamOutStrategy outputStrategy{ out };
  outputStrategy.writeOutput(bracket);
  CHECK(out->str( ) == getExpectedOutput( ));// NOLINT(cppcoreguidelines-avoid-do-while)
}
