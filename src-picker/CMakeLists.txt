
set(SOURCES
  Bracket.cpp
  BracketData.cpp
  CommandLineParser_CLI.cpp
  Logger_Spdlog.cpp
  LogManager.cpp
  OutputStrategy_Factory.cpp
  OutputStrategy_FileOut.cpp
  OutputStrategy_StdOut.cpp
  Problem.cpp
  ProblemData.cpp
  RandomizationStrategy_Factory.cpp
  RandomizationStrategy_MersenneTwister.cpp
  RandomizationStrategy_MinStdRand.cpp
  RandomizationStrategy_StdRand.cpp
  SelectionStrategy_CoinFlip.cpp
  SelectionStrategy_Factory.cpp
  SelectionStrategy_RankDeterministic.cpp
  SelectionStrategy_SpreadBased.cpp
  TeamData.cpp
)

set(PICKER_ENABLE_LOGGING ${MarchMadnessPicker_ENABLE_LOGGING})
configure_file(PickerConfig.hpp.in PickerConfig.hpp)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME}
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${PROJECT_NAME}
  PUBLIC
  MarchMadnessPicker::MarchMadnessPicker_warnings
  MarchMadnessPicker::MarchMadnessPicker_options
  CLI11::CLI11
  nlohmann_json::nlohmann_json
  spdlog::spdlog
  PRIVATE
  fmt::fmt)

set(EXE_NAME picker)
add_executable(${EXE_NAME} main.cpp)
target_link_libraries(${EXE_NAME}
  PRIVATE
  ${PROJECT_NAME})
