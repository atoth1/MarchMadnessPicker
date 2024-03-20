#include <iostream>
#include <memory>

#include "nlohmann/json.hpp"

#include "Bracket.hpp"
#include "OutputStrategy.hpp"
#include "OutputStrategy_StdOut.hpp"

void picker::StdOutStrategy::writeOutput(const picker::Bracket& bracket) const { std::cout << bracket; }

std::shared_ptr<picker::OutputStrategy> picker::StdOutStrategyFactory::create(const nlohmann::json& /*params*/) const
{
  return std::make_shared<StdOutStrategy>( );
}
