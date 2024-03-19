#include <random>

#include "RandomizationStrategy_MersenneTwister.hpp"

picker::MersenneTwisterStrategy::MersenneTwisterStrategy(const std::mt19937::result_type seed)
  : generator(seed), dist(0.0, 1.0)
{}

double picker::MersenneTwisterStrategy::getRandom( ) { return dist(generator); }