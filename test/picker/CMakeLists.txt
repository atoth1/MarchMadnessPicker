include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)



#add_executable(tests tests.cpp)
#target_link_libraries(
#  tests
#  PRIVATE MarchMadnessPicker::MarchMadnessPicker_warnings
#          MarchMadnessPicker::MarchMadnessPicker_options
#          MarchMadnessPicker::sample_library
#          Catch2::Catch2WithMain)

#if(WIN32 AND BUILD_SHARED_LIBS)
#  add_custom_command(
#    TARGET tests
#    PRE_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:tests> $<TARGET_FILE_DIR:tests>
#    COMMAND_EXPAND_LISTS)
#endif()

# automatically discover tests that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
# to whatever you want, or use different for different binaries
#catch_discover_tests(
#  tests
#  TEST_PREFIX
#  "unittests."
#  REPORTER
#  XML
#  OUTPUT_DIR
#  .
#  OUTPUT_PREFIX
#  "unittests."
#  OUTPUT_SUFFIX
#  .xml)


