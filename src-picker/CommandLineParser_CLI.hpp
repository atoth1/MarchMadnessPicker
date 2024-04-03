#ifndef PICKER_COMMAND_LINE_PARSER_CLI_HPP
#define PICKER_COMMAND_LINE_PARSER_CLI_HPP

#include <optional>

#include "CommandLineParser.hpp"

namespace picker {

class CLIParser : public CommandLineParser
{
public:
  std::optional<CommandLineParseResult> parse(int argc, const char* const* argv) const override;
};

}// namespace picker

#endif