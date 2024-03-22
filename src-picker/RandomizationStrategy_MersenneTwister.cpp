#include <memory>
#include <random>

#include "nlohmann/json.hpp"

#include "RandomizationStrategy.hpp"
#include "RandomizationStrategy_MersenneTwister.hpp"

picker::MersenneTwisterStrategy::MersenneTwisterStrategy(const std::mt19937::result_type seed)
  : generator(seed), dist(0.0, 1.0)
{}

double picker::MersenneTwisterStrategy::getRandom( ) { return dist(generator); }

std::shared_ptr<picker::RandomizationStrategy> picker::MersenneTwisterStrategyFactory::create(
  const nlohmann::json& params) const// NOLINT(misc-include-cleaner)
{
  std::mt19937::result_type seed = std::random_device{ }( );
  if (params.contains("seed")) { params.at("seed").get_to(seed); }
  return std::make_shared<MersenneTwisterStrategy>(seed);
}
