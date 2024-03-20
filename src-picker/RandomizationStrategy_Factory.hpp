#ifndef PICKER_RANDOMIZATION_STRATEGY_FACTORY_HPP
#define PICKER_RANDOMIZATION_STRATEGY_FACTORY_HPP

#include <memory>
#include <string_view>
#include <unordered_map>

#include "nlohmann/json_fwd.hpp"

#include "GenericFactory.hpp"

namespace picker {

class RandomizationStrategy;

class RandomizationStrategyFactory
{
public:
  static constexpr std::string_view MERSENNE_TWISTER_LABEL = "mersenne-twister";

  static constexpr std::string_view MINSTD_RAND_LABEL = "minstd-rand";

  static constexpr std::string_view STD_RAND_LABEL = "std-rand";

  RandomizationStrategyFactory( ) = default;

  void registerFactory(std::string_view type, std::unique_ptr<GenericFactory<RandomizationStrategy>>&& factory);

  std::shared_ptr<RandomizationStrategy> create(std::string_view type, const nlohmann::json& params) const;

private:
  std::unordered_map<std::string_view, std::unique_ptr<GenericFactory<RandomizationStrategy>>> factories{ };
};

}// namespace picker

#endif
