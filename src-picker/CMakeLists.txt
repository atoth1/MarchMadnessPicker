
set(SOURCES
  BracketData.cpp
  ProblemData.cpp
  RandomizationStrategy_MersenneTwister.cpp
  RandomizationStrategy_MinStdRand.cpp
  RandomizationStrategy_StdRand.cpp
  SelectionStrategy_CoinFlip.cpp
  SelectionStrategy_RankDeterministic.cpp
  SelectionStrategy_SpreadBased.cpp
  TeamData.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(${PROJECT_NAME} MarchMadnessPicker_options)
target_link_libraries(${PROJECT_NAME} MarchMadnessPicker_warnings)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

set(EXE_NAME picker)
add_executable(${EXE_NAME} main.cpp)
target_link_libraries(${EXE_NAME} CLI11::CLI11)
target_link_libraries(${EXE_NAME} ${PROJECT_NAME})
