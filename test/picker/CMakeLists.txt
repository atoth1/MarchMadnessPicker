include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

configure_file("test-team-data.json" "test-team-data.json" COPYONLY)

set(SOURCES
  BracketDataTest.cpp
  BracketTest.cpp
  OutputStrategyFactoryTest.cpp
  OutputStrategyTest.cpp
  ProblemDataTest.cpp
  RandomizationStrategyFactoryTest.cpp
  RandomizationStrategyTest.cpp
  SelectionStrategyTest.cpp
  TeamDataTest.cpp
  TestUtils.cpp
)

add_executable(unit-tests ${SOURCES})
target_link_libraries(unit-tests
  PRIVATE
  ${PROJECT_NAME}
  Catch2::Catch2WithMain
  fmt::fmt)

#if(WIN32 AND BUILD_SHARED_LIBS)
#  add_custom_command(
#    TARGET tests
#    PRE_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:tests> $<TARGET_FILE_DIR:tests>
#    COMMAND_EXPAND_LISTS)
#endif()

# automatically discover tests that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
# to whatever you want, or use different for different binaries
catch_discover_tests(
  unit-tests
  TEST_PREFIX
  "unittests."
  REPORTER
  XML
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "unittests."
  OUTPUT_SUFFIX
  .xml)
