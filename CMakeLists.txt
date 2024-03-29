cmake_minimum_required(VERSION 3.21)

# This template attempts to be "fetch_content"-able
# so that it works well with tools like CPM or other
# manual dependency management

# Only set the cxx_standard if it is not set by someone else
if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the project name and language
project(
  MarchMadnessPicker
  VERSION 0.0.1
  DESCRIPTION ""
  HOMEPAGE_URL "https://github.com/atoth1/MarchMadnessPicker"
  LANGUAGES CXX C)

include(cmake/PreventInSourceBuilds.cmake)
include(ProjectOptions.cmake)

MarchMadnessPicker_setup_options()

MarchMadnessPicker_global_options()
include(Dependencies.cmake)
MarchMadnessPicker_setup_dependencies()

MarchMadnessPicker_local_options()

set(GIT_SHA
    "Unknown"
    CACHE STRING "SHA this build was generated from")
string(
  SUBSTRING "${GIT_SHA}"
            0
            8
            GIT_SHORT_SHA)

target_compile_features(MarchMadnessPicker_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

add_library(MarchMadnessPicker::MarchMadnessPicker_options ALIAS MarchMadnessPicker_options)
add_library(MarchMadnessPicker::MarchMadnessPicker_warnings ALIAS MarchMadnessPicker_warnings)

# Adding the src
add_subdirectory(src-picker)
add_subdirectory(kenpom-scraper)

# Include python for kenpom-scraper tests
find_package(Python REQUIRED)

# Adding the tests
include(CTest)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()

# If MSVC is being used, and ASAN is enabled, we need to set the debugger environment
# so that it behaves well with MSVC's debugger, and we can run the target from visual studio
if(MSVC)
  get_all_installable_targets(all_targets)
  message("all_targets=${all_targets}")
  set_target_properties(${all_targets} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$(VC_ExecutablePath_x64);%PATH%")
endif()

