
function(ADD_TEST_CASE test_name)
  configure_file("${test_name}.py" "${test_name}.py" COPYONLY)
  add_test(NAME ${test_name}
    COMMAND ${Python_EXECUTABLE} -m unittest ${CMAKE_CURRENT_BINARY_DIR}/${test_name}.py
  )
  set_tests_properties(${test_name}
      PROPERTIES ENVIRONMENT "PYTHONPATH=${PROJECT_BINARY_DIR}/kenpom-scraper:$ENV{PYTHONPATH}"
  )
endfunction(ADD_TEST_CASE test_name)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  ADD_TEST_CASE("test_http_request")
  ADD_TEST_CASE("test_html_parse")
  ADD_TEST_CASE("test_json_writer")
endif()
