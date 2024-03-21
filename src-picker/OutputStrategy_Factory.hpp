#ifndef PICKER_OUTPUT_STRATEGY_FACTORY_HPP
#define PICKER_OUTPUT_STRATEGY_FACTORY_HPP

#include <memory>
#include <string_view>
#include <unordered_map>

#include "nlohmann/json_fwd.hpp"

#include "GenericFactory.hpp"

namespace picker {

class OutputStrategy;

class OutputStrategyFactory
{
public:
  using FactoryType = GenericFactory<OutputStrategy>;

  OutputStrategyFactory( ) = default;

  void registerFactory(std::string_view type, std::unique_ptr<FactoryType>&& factory);

  std::shared_ptr<OutputStrategy> create(std::string_view type, const nlohmann::json& params) const;

private:
  std::unordered_map<std::string_view, std::unique_ptr<FactoryType>> factories{ };
};

}// namespace picker

#endif
