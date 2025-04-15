cmake_minimum_required(VERSION 3.5)

project(GreedySnake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Release")

# Enable testing
enable_testing()

# Find ncurses for terminal rendering
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Find SFML components for graphical rendering
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Add all subdirectories to include path
file(GLOB_RECURSE ALL_SUBDIRS LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/src/*")
foreach(SUBDIR ${ALL_SUBDIRS})
    if(IS_DIRECTORY ${SUBDIR})
        include_directories(${SUBDIR})
    endif()
endforeach()

# Find source files (excluding test files)
file(GLOB_RECURSE SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
list(FILTER SOURCES EXCLUDE REGEX ".*tests/.*\\.cpp$")

file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

# Debug information
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Source files found:")
    foreach(SOURCE ${SOURCES})
        message(STATUS "  ${SOURCE}")
    endforeach()

    message(STATUS "Headers:")
    foreach(HEADER ${HEADERS})
        message(STATUS "  ${HEADER}")
    endforeach()
endif()

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} 
    ${CURSES_LIBRARIES}
    sfml-system sfml-window sfml-graphics sfml-audio
)

# Add Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Find test files
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/tests/*.cpp")

# Get sources for tests (excluding main.cpp)
file(GLOB_RECURSE SOURCES_FOR_TESTS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
list(FILTER SOURCES_FOR_TESTS EXCLUDE REGEX ".*tests/.*\\.cpp$")
list(FILTER SOURCES_FOR_TESTS EXCLUDE REGEX ".*main\\.cpp$")

# Add test executable
add_executable(
  run_tests
  ${TEST_SOURCES}
  ${SOURCES_FOR_TESTS}
)
target_link_libraries(
  run_tests
  GTest::gtest
  ${CURSES_LIBRARIES}
  sfml-system sfml-window sfml-graphics sfml-audio
)

include(GoogleTest)
gtest_discover_tests(run_tests)