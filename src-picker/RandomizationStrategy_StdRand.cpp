#include <cstdlib>
#include <memory>
#include <random>

#include "fmt/core.h"
#include "nlohmann/json.hpp"

#include "LogManager.hpp"
#include "RandomizationStrategy.hpp"
#include "RandomizationStrategy_StdRand.hpp"

picker::StdRandStrategy::StdRandStrategy(const unsigned seed)
{
  logDebug(fmt::format("Seeding std::rand with value {}.", seed));
  std::srand(seed);
}

double picker::StdRandStrategy::getRandom( )
{
  // NOLINTNEXTLINE
  double ret = static_cast<double>(std::rand( )) / RAND_MAX;
  logDebug(fmt::format("Generated random number {}.", ret));
  return ret;
}

std::shared_ptr<picker::RandomizationStrategy> picker::StdRandStrategyFactory::create(
  const nlohmann::json& params) const// NOLINT(misc-include-cleaner)
{
  unsigned seed = std::random_device{ }( );
  if (params.contains("seed")) { params.at("seed").get_to(seed); }
  return std::make_shared<StdRandStrategy>(seed);
}
