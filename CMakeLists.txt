cmake_minimum_required(VERSION 3.20)
project(scratchpad)

add_library(project-options INTERFACE)

include(${CMAKE_SOURCE_DIR}/cmake/Sanitizers.cmake)
enable_sanitizers(project-options)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Set CMAKE_BUILD_TYPE if not set
get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(isMultiConfig)
    if(NOT "Profile" IN_LIST CMAKE_CONFIGURATION_TYPES)
        list(APPEND CMAKE_CONFIGURATION_TYPES Profile)
    endif()
else()
    set(allowedBuildTypes Debug Release Profile)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY
    STRINGS "${allowedBuildTypes}"
    )
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
    elseif(NOT CMAKE_BUILD_TYPE IN_LIST allowedBuildTypes)
        message(FATAL_ERROR "Unknown build type: ${CMAKE_BUILD_TYPE}")
    endif()
endif()

# Force color diagnostics
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics")
  endif ()
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdiagnostics-color")
endif ()

add_library(compiler-warnings INTERFACE)
target_compile_options(compiler-warnings
    INTERFACE
        -Wall
        -Wextra
)

add_library(util)
target_include_directories(util PUBLIC src/util)
target_sources(util PRIVATE src/util/ostream.c)
target_link_libraries(util PRIVATE compiler-warnings)

add_library(bst)
target_include_directories(bst PUBLIC src/bst)
target_sources(bst PRIVATE src/bst/bst.c)
target_link_libraries(bst PRIVATE compiler-warnings)

add_executable(ostream-test)
target_sources(ostream-test PRIVATE test/ostream-test.c)
target_link_libraries(ostream-test PRIVATE util compiler-warnings)

add_executable(bst-test)
target_sources(bst-test PRIVATE test/bst-test.c)
target_link_libraries(bst-test PRIVATE project-options bst util compiler-warnings)