include(cmake/SystemLink.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)


macro(MarchMadnessPicker_supports_sanitizers)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
    set(SUPPORTS_UBSAN ON)
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    set(SUPPORTS_ASAN ON)
  endif()
endmacro()

macro(MarchMadnessPicker_setup_options)
  option(MarchMadnessPicker_ENABLE_HARDENING "Enable hardening" ON)
  option(MarchMadnessPicker_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  cmake_dependent_option(
    MarchMadnessPicker_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    MarchMadnessPicker_ENABLE_HARDENING
    OFF)

  MarchMadnessPicker_supports_sanitizers()

  option(MarchMadnessPicker_ENABLE_IPO "Enable IPO/LTO" ON)
  option(MarchMadnessPicker_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
  option(MarchMadnessPicker_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
  option(MarchMadnessPicker_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
  option(MarchMadnessPicker_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
  option(MarchMadnessPicker_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
  option(MarchMadnessPicker_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
  option(MarchMadnessPicker_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
  option(MarchMadnessPicker_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
  option(MarchMadnessPicker_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
  option(MarchMadnessPicker_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
  option(MarchMadnessPicker_ENABLE_PCH "Enable precompiled headers" OFF)
  option(MarchMadnessPicker_ENABLE_CACHE "Enable ccache" ON)
  option(MarchMadnessPicker_ENABLE_LOGGING "Enable run-time logging" ON)

endmacro()

macro(MarchMadnessPicker_global_options)
  if(MarchMadnessPicker_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    MarchMadnessPicker_enable_ipo()
  endif()

  MarchMadnessPicker_supports_sanitizers()

  if(MarchMadnessPicker_ENABLE_HARDENING AND MarchMadnessPicker_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR MarchMadnessPicker_ENABLE_SANITIZER_UNDEFINED
       OR MarchMadnessPicker_ENABLE_SANITIZER_ADDRESS
       OR MarchMadnessPicker_ENABLE_SANITIZER_THREAD
       OR MarchMadnessPicker_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${MarchMadnessPicker_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${MarchMadnessPicker_ENABLE_SANITIZER_UNDEFINED}")
    MarchMadnessPicker_enable_hardening(MarchMadnessPicker_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(MarchMadnessPicker_local_options)
  include(cmake/StandardProjectSettings.cmake)

  add_library(MarchMadnessPicker_warnings INTERFACE)
  add_library(MarchMadnessPicker_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  MarchMadnessPicker_set_project_warnings(
    MarchMadnessPicker_warnings
    ${MarchMadnessPicker_WARNINGS_AS_ERRORS}
    ""
    ""
    "")

  if(MarchMadnessPicker_ENABLE_USER_LINKER)
    include(cmake/Linker.cmake)
    configure_linker(MarchMadnessPicker_options)
  endif()

  include(cmake/Sanitizers.cmake)
  MarchMadnessPicker_enable_sanitizers(
    MarchMadnessPicker_options
    ${MarchMadnessPicker_ENABLE_SANITIZER_ADDRESS}
    ${MarchMadnessPicker_ENABLE_SANITIZER_LEAK}
    ${MarchMadnessPicker_ENABLE_SANITIZER_UNDEFINED}
    ${MarchMadnessPicker_ENABLE_SANITIZER_THREAD}
    ${MarchMadnessPicker_ENABLE_SANITIZER_MEMORY})

  set_target_properties(MarchMadnessPicker_options PROPERTIES UNITY_BUILD ${MarchMadnessPicker_ENABLE_UNITY_BUILD})

  if(MarchMadnessPicker_ENABLE_PCH)
    target_precompile_headers(
      MarchMadnessPicker_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(MarchMadnessPicker_ENABLE_CACHE)
    include(cmake/Cache.cmake)
    MarchMadnessPicker_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(MarchMadnessPicker_ENABLE_CLANG_TIDY)
    MarchMadnessPicker_enable_clang_tidy(MarchMadnessPicker_options ${MarchMadnessPicker_WARNINGS_AS_ERRORS})
  endif()

  if(MarchMadnessPicker_ENABLE_CPPCHECK)
    MarchMadnessPicker_enable_cppcheck(${MarchMadnessPicker_WARNINGS_AS_ERRORS} "" # override cppcheck options
    )
  endif()

  if(MarchMadnessPicker_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    MarchMadnessPicker_enable_coverage(MarchMadnessPicker_options)
  endif()

  if(MarchMadnessPicker_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(MarchMadnessPicker_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(MarchMadnessPicker_ENABLE_HARDENING AND NOT MarchMadnessPicker_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR MarchMadnessPicker_ENABLE_SANITIZER_UNDEFINED
       OR MarchMadnessPicker_ENABLE_SANITIZER_ADDRESS
       OR MarchMadnessPicker_ENABLE_SANITIZER_THREAD
       OR MarchMadnessPicker_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    MarchMadnessPicker_enable_hardening(MarchMadnessPicker_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
