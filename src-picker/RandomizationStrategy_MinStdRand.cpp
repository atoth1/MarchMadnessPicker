#include <random>

#include "RandomizationStrategy_MinStdRand.hpp"

picker::MinStdRandStrategy::MinStdRandStrategy(const std::minstd_rand::result_type seed)
  : generator(seed), dist(0.0, 1.0)
{}

double picker::MinStdRandStrategy::getRandom( ) { return dist(generator); }
