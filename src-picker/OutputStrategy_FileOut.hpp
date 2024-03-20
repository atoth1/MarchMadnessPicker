#ifndef PICKER_OUTPUT_STRATEGY_FILEOUT_HPP
#define PICKER_OUTPUT_STRATEGY_FILEOUT_HPP

#include <fstream>
#include <memory>
#include <string>

#include "GenericFactory.hpp"
#include "OutputStrategy.hpp"

namespace picker {

struct Bracket;

class FileOutStrategy : public picker::OutputStrategy
{
public:
  explicit FileOutStrategy(const std::string& fileName);

  void writeOutput(const Bracket& bracket) const override;

private:
  std::unique_ptr<std::ofstream> out;
};

class FileOutStrategyFactory : public GenericFactory<OutputStrategy>
{
public:
  std::shared_ptr<OutputStrategy> create(const nlohmann::json& params) const override;
};

}// namespace picker

#endif
