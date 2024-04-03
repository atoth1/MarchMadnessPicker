#include <exception>
#include <iostream>
#include <memory>

#include "CommandLineParser.hpp"
#include "CommandLineParser_CLI.hpp"
#include "LogManager.hpp"
#include "Logger_Spdlog.hpp"
#include "Problem.hpp"

int main(int argc, char** argv)
{
  try {
    const auto clp = std::make_unique<picker::CLIParser>( );
    const auto parseResult = clp->parse(argc, argv);

    if (parseResult) {
      picker::setGlobalLogger(std::make_unique<picker::SpdlogLogger>(
        picker::SpdlogLogger::LogLevels{ parseResult->screenLogLevel, parseResult->fileLogLevel }));
      picker::Problem problem(parseResult->inputFile);
      problem.setup( );
      problem.run( );
    }
  } catch (const std::exception& e) {
    std::cerr << "Caught exception: " << e.what( ) << '\n';
  }
}
