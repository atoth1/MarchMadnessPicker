#include <exception>
#include <iostream>
#include <memory>
#include <string>

#include "CLI/CLI.hpp"

#include "Constants.hpp"
#include "OutputStrategy_FileOut.hpp"
#include "OutputStrategy_StdOut.hpp"
#include "Problem.hpp"
#include "ProblemData.hpp"
#include "RandomizationStrategy_MersenneTwister.hpp"
#include "RandomizationStrategy_MinStdRand.hpp"
#include "RandomizationStrategy_StdRand.hpp"
#include "SelectionStrategy_CoinFlip.hpp"
#include "SelectionStrategy_RankDeterministic.hpp"
#include "SelectionStrategy_SpreadBased.hpp"

int main(int argc, char** argv)
{
  try {
    CLI::App app{ "Simulator for producing March Madness brackets.", "picker" };
    std::string jsonInput{ };
    app.add_option("-i, --input", jsonInput, "Path for JSON input file")->required( );
    CLI11_PARSE(app, argc, argv);

    picker::Problem problem(jsonInput);

    auto setupRandomizationStrategy = [&]( ) {
      problem.registerRandomizationStrategyFactory(
        picker::MERSENNE_TWISTER_STRATEGY_LABEL, std::make_unique<picker::MersenneTwisterStrategyFactory>( ));
      problem.registerRandomizationStrategyFactory(
        picker::MINSTD_RAND_STRATEGY_LABEL, std::make_unique<picker::MinStdRandStrategyFactory>( ));
      problem.registerRandomizationStrategyFactory(
        picker::STD_RAND_STRATEGY_LABEL, std::make_unique<picker::StdRandStrategyFactory>( ));
      problem.createRandomizationStrategy( );
    };
    setupRandomizationStrategy( );

    auto setupSelectionStrategy = [&]( ) {
      problem.registerSelectionStrategyFactory(picker::COIN_FLIP_STRATEGY_LABEL,
        std::make_unique<picker::CoinFlipStrategyFactory>(problem.getRandomizationStrategy( )));
      problem.registerSelectionStrategyFactory(picker::RANK_DETERMINISTIC_STRATEGY_LABEL,
        std::make_unique<picker::RankDeterministicStrategyFactory>(&problem.getProblemData( ).teamDataLookup));
      problem.registerSelectionStrategyFactory(picker::SPREAD_BASED_STRATEGY_LABEL,
        std::make_unique<picker::SpreadBasedStrategyFactory>(
          problem.getRandomizationStrategy( ), &problem.getProblemData( ).teamDataLookup));
      problem.createSelectionStrategy( );
    };
    setupSelectionStrategy( );

    auto setupOutputStrategy = [&]( ) {
      problem.registerOutputStrategyFactory(
        picker::FILE_OUT_STRATEGY_LABEL, std::make_unique<picker::FileOutStrategyFactory>( ));
      problem.registerOutputStrategyFactory(
        picker::STD_OUT_STRATEGY_LABEL, std::make_unique<picker::StdOutStrategyFactory>( ));
      problem.createOutputStrategy( );
    };
    setupOutputStrategy( );

    problem.run( );
  } catch (const std::exception& e) {
    std::cerr << "Caught exception: " << e.what( ) << '\n';
  }
}
