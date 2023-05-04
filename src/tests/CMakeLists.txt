# CMakeLists.txt for the test directory

# Set the minimum version of CMake required for this project
cmake_minimum_required(VERSION 3.10)

# Define the project name
if(NOT PROJECT_NAME)
    set(PROJECT_NAME "Project-tests")
endif()
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find the required packages
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
find_package(GTest REQUIRED)

include_directories(
  ${PROJECT_SOURCE_DIR}/../
)

# Set the source files for the tests
set(TEST_SOURCES
        main.cc
        core/MLPBuilderTest.cc
        core/graph/GraphTest.cc
        core/graph/GraphLayerTest.cc
        core/graph/GraphModelTest.cc
        core/DatasetReadingTest.cc
        core/matrix/MatrixTest.cc
        core/matrix/MatrixModelTest.cc
)

# Add the executable for the tests
add_executable(${PROJECT_NAME} ${TEST_SOURCES})

# Link the required libraries
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::GTest GTest::Main)

# Set the include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Set the output directory for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../../bin")
