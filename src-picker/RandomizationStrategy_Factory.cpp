#include <memory>
#include <string_view>
#include <utility>

#include "nlohmann/json.hpp"

#include "GenericFactory.hpp"
#include "RandomizationStrategy_Factory.hpp"

void picker::RandomizationStrategyFactory::registerFactory(std::string_view type,
  std::unique_ptr<GenericFactory<RandomizationStrategy>>&& factory)
{
  factories[type] = std::move(factory);
}

std::shared_ptr<picker::RandomizationStrategy> picker::RandomizationStrategyFactory::create(std::string_view type,
  const nlohmann::json& params) const
{
  if (auto factoryIt = factories.find(type); factoryIt != factories.end( )) {
    return factoryIt->second->create(params);
  }
  return nullptr;
}