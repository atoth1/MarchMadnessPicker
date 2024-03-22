#include <memory>
#include <sstream>
#include <string>

#include "catch2/catch_test_macros.hpp"

#include "Bracket.hpp"
#include "OutputStrategy.hpp"
#include "TestUtils.hpp"

TEST_CASE("OutputStrategy - expected output", "[OutputStrategy]")// NOLINT
{
  const auto selectionStrategy = std::make_shared<LexicographicCompareStrategy>( );
  const auto bracket = picker::makeBracket(getTestBracketData( ), selectionStrategy);

  auto out = std::make_shared<std::ostringstream>( );
  const StringstreamOutStrategy stringstreamOutputStrategy{ out };
  const picker::OutputStrategy& outputStrategy = stringstreamOutputStrategy;
  outputStrategy.writeOutput(bracket);
  CHECK(out->str( ) == getExpectedOutput( ));// NOLINT
}
