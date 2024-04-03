#ifndef PICKER_COMMAND_LINE_PARSER_HPP
#define PICKER_COMMAND_LINE_PARSER_HPP

#include <optional>
#include <string>

#include "Logger.hpp"

namespace picker {

struct CommandLineParseResult
{
  std::string inputFile{ };
  LogLevel screenLogLevel{ LogLevel::WARNING };
  LogLevel fileLogLevel{ LogLevel::OFF };
};

class CommandLineParser
{
public:
  virtual ~CommandLineParser( ) = default;

  CommandLineParser(const CommandLineParser&) = delete;

  CommandLineParser(CommandLineParser&&) = delete;

  CommandLineParser& operator=(const CommandLineParser&) = delete;

  CommandLineParser& operator=(CommandLineParser&&) = delete;

  // With c++23 support this could make more sense as std::expected, but for now a return value
  // of std::nullopt suffices to indicate a failed parse.
  virtual std::optional<CommandLineParseResult> parse(int argc, const char* const* argv) const = 0;

protected:
  CommandLineParser( ) = default;
};

}// namespace picker

#endif
