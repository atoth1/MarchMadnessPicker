#include <exception>
#include <iostream>
#include <string>

#include "CLI/CLI.hpp"

int main(int argc, char** argv)
{
  try {
    CLI::App app{ "Simulator for producing March Madness brackets.", "picker" };
    std::string jsonInput{ };
    app.add_option("-i, --input", jsonInput, "Path for JSON input file")->required( );
    CLI11_PARSE(app, argc, argv);

    // asdf
  } catch (const std::exception& e) {
    std::cerr << "Caught exception: " << e.what( ) << '\n';
  }
}