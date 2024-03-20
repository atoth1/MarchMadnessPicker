#include <cstdlib>
#include <memory>
#include <random>

#include "nlohmann/json.hpp"

#include "RandomizationStrategy.hpp"
#include "RandomizationStrategy_StdRand.hpp"

picker::StdRandStrategy::StdRandStrategy(const unsigned seed) { std::srand(seed); }

double picker::StdRandStrategy::getRandom( ) { return static_cast<double>(std::rand( )) / RAND_MAX; }// NOLINT

std::shared_ptr<picker::RandomizationStrategy> picker::StdRandStrategyFactory::create(
  const nlohmann::json& params) const
{
  unsigned seed = std::random_device{ }( );
  if (params.contains("seed")) { params.at("seed").get_to(seed); }
  return std::make_shared<StdRandStrategy>(seed);
}
