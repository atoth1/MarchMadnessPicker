#include <memory>
#include <random>

#include "nlohmann/json.hpp"

#include "RandomizationStrategy.hpp"
#include "RandomizationStrategy_MinStdRand.hpp"

picker::MinStdRandStrategy::MinStdRandStrategy(const std::minstd_rand::result_type seed)
  : generator(seed), dist(0.0, 1.0)
{}

double picker::MinStdRandStrategy::getRandom( ) { return dist(generator); }

std::shared_ptr<picker::RandomizationStrategy> picker::MinStdRandStrategyFactory::create(
  const nlohmann::json& params) const// NOLINT(misc-include-cleaner)
{
  std::minstd_rand::result_type seed = std::random_device{ }( );
  if (params.contains("seed")) { params.at("seed").get_to(seed); }
  return std::make_shared<MinStdRandStrategy>(seed);
}
