#include <cstdlib>
#include <memory>
#include <random>

#include "nlohmann/json.hpp"

#include "RandomizationStrategy.hpp"
#include "RandomizationStrategy_StdRand.hpp"

picker::StdRandStrategy::StdRandStrategy(const unsigned seed) { std::srand(seed); }

// NOLINTNEXTLINE(cert-msc30-c, cert-msc50-cpp, concurrency-mt-unsafe)
double picker::StdRandStrategy::getRandom( ) { return static_cast<double>(std::rand( )) / RAND_MAX; }

std::shared_ptr<picker::RandomizationStrategy> picker::StdRandStrategyFactory::create(
  const nlohmann::json& params) const// NOLINT(misc-include-cleaner)
{
  unsigned seed = std::random_device{ }( );
  if (params.contains("seed")) { params.at("seed").get_to(seed); }
  return std::make_shared<StdRandStrategy>(seed);
}
