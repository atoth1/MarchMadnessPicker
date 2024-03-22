#include <fstream>
#include <memory>
#include <string>

#include "nlohmann/json.hpp"

#include "Bracket.hpp"
#include "OutputStrategy.hpp"
#include "OutputStrategy_FileOut.hpp"

picker::FileOutStrategy::FileOutStrategy(const std::string& fileName) : out(std::make_unique<std::ofstream>(fileName))
{}

void picker::FileOutStrategy::writeOutput(const picker::Bracket& bracket) const { (*out) << bracket; }

// NOLINTNEXTLINE(misc-include-cleaner)
std::shared_ptr<picker::OutputStrategy> picker::FileOutStrategyFactory::create(const nlohmann::json& params) const
{
  std::string fileName{ "bracket.txt" };
  if (params.contains("file_name")) { params.at("file_name").get_to(fileName); }
  return std::make_shared<FileOutStrategy>(fileName);
}
