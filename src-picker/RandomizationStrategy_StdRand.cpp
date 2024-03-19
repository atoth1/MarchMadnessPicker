#include <cstdlib>

#include "RandomizationStrategy_StdRand.hpp"

picker::StdRandStrategy::StdRandStrategy(const unsigned seed) { std::srand(seed); }

double picker::StdRandStrategy::getRandom( ) { return static_cast<double>(std::rand( )) / RAND_MAX; }// NOLINT
