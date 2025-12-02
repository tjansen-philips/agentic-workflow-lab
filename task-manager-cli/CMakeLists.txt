cmake_minimum_required(VERSION 3.15)
project(TaskManagerCLI VERSION 1.0 LANGUAGES CXX)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Coverage flags (optional, enabled with -DCOVERAGE=ON)
option(COVERAGE "Enable code coverage" OFF)
if(COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    endif()
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Source files
set(SOURCES
    src/task.cpp
    src/task_repository.cpp
    src/task_manager.cpp
    src/cli.cpp
)

# Main executable
add_executable(task-manager src/main.cpp ${SOURCES})

# Enable testing
enable_testing()

# Fetch Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Test executable
add_executable(task-manager-tests
    tests/test_task.cpp
    tests/test_task_repository.cpp
    tests/test_task_manager.cpp
    tests/test_cli.cpp
    tests/test_integration.cpp
    ${SOURCES}
)

target_link_libraries(task-manager-tests GTest::gtest_main)

# Add tests
include(GoogleTest)
gtest_discover_tests(task-manager-tests)
