
#include "TestUtils.hpp"

DeterministicStrategy::DeterministicStrategy(const double inVal) : val(inVal) {}

double DeterministicStrategy::getRandom( ) { return val; }