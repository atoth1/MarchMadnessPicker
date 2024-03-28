#include <memory>
#include <random>

#include "fmt/core.h"
#include "nlohmann/json.hpp"

#include "LogManager.hpp"
#include "RandomizationStrategy.hpp"
#include "RandomizationStrategy_MersenneTwister.hpp"

picker::MersenneTwisterStrategy::MersenneTwisterStrategy(const std::mt19937::result_type seed)
  : generator(seed), dist(0.0, 1.0)
{
  logDebug(fmt::format("Seeding std::mt19937 generator with seed {}.", seed));
}

double picker::MersenneTwisterStrategy::getRandom( )
{
  double ret = dist(generator);
  logDebug(fmt::format("Generated random number {}.", ret));
  return ret;
}

std::shared_ptr<picker::RandomizationStrategy> picker::MersenneTwisterStrategyFactory::create(
  const nlohmann::json& params) const// NOLINT(misc-include-cleaner)
{
  std::mt19937::result_type seed = std::random_device{ }( );
  if (params.contains("seed")) { params.at("seed").get_to(seed); }
  return std::make_shared<MersenneTwisterStrategy>(seed);
}
