#include <string>

#include "TestUtils.hpp"

// void StringOutputStrategy::writeOutput( ) {}

DeterministicStrategy::DeterministicStrategy(const double inVal) : val(inVal) {}

double DeterministicStrategy::getRandom( ) { return val; }

std::string LexicographicCompareStrategy::selectWinner(const std::string& team1, const std::string& team2)
{
  return team1 < team2 ? team1 : team2;
}
