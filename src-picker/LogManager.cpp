#include <memory>
#include <string_view>
#include <utility>

#include "LogManager.hpp"
#include "Logger.hpp"
#include "PickerConfig.hpp"

void picker::setGlobalLogger(std::unique_ptr<Logger>&& inLogger)
{
  if constexpr (picker::enableLogging) { LogManager::getInstance( ).setLogger(std::move(inLogger)); }
}

void picker::logTrace(std::string_view message)
{
  if constexpr (picker::enableLogging) { LogManager::getInstance( ).trace(message); }
}

void picker::logDebug(std::string_view message)
{
  if constexpr (picker::enableLogging) { LogManager::getInstance( ).debug(message); }
}

void picker::logInfo(std::string_view message)
{
  if constexpr (picker::enableLogging) { LogManager::getInstance( ).info(message); }
}

void picker::logWarning(std::string_view message)
{
  if constexpr (picker::enableLogging) { LogManager::getInstance( ).warning(message); }
}

void picker::logError(std::string_view message)
{
  if constexpr (picker::enableLogging) { LogManager::getInstance( ).error(message); }
}

void picker::logCritical(std::string_view message)
{
  if constexpr (picker::enableLogging) { LogManager::getInstance( ).critical(message); }
}

picker::LogManager& picker::LogManager::getInstance( )
{
  static picker::LogManager manager{ };
  return manager;
}

void picker::LogManager::setLogger(std::unique_ptr<Logger>&& inLogger) { logger = std::move(inLogger); }

void picker::LogManager::trace(std::string_view message) const
{
  if (logger) { logger->trace(message); }
}

void picker::LogManager::debug(std::string_view message) const
{
  if (logger) { logger->debug(message); }
}

void picker::LogManager::info(std::string_view message) const
{
  if (logger) { logger->info(message); }
}

void picker::LogManager::warning(std::string_view message) const
{
  if (logger) { logger->warning(message); }
}

void picker::LogManager::error(std::string_view message) const
{
  if (logger) { logger->error(message); }
}

void picker::LogManager::critical(std::string_view message) const
{
  if (logger) { logger->critical(message); }
}
