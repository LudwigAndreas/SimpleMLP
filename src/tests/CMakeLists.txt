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

set(CMAKE_CXX_FLAGS "-Wall -Wextra -g -Og -fprofile-arcs -ftest-coverage")

# Find the required packages
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(
  ${SRC_DIR}
  ${SRC_DIR}/libs21/include
)

set(PROJECT_SOURCES 
        ../core/DatasetReading.cc
        ../core/graph/MLPGraphLayer.cc
        ../core/graph/MLPGraphModel.cc
        ../core/graph/MLPGraphNode.cc
        ../core/LetterRecognitionMlpModelBuilder.cc
        ../core/matrix/MLPMatrixLayer.cc
        ../core/matrix/MLPMatrixModel.cc
        ../core/utils/ActivationFunction.cc
        ../core/utils/AFLibrary.cc
        ../core/utils/ModelMetrics.cc
        ../libs21/src/s21_load_bmp.cc
        ../libs21/src/s21_split.cc
        ../libs21/src/s21_to_lower.cc
        ../libs21/src/s21_to_upper.cc
)

# Set the source files for the tests
set(TEST_SOURCES
        main.cc
        core/graph/GraphLayerTest.cc
        # core/graph/GraphModelTest.cc
        core/matrix/MatrixTest.cc
        core/matrix/MatrixModelTest.cc
)

# Add the executable for the tests
add_executable(${PROJECT_NAME} ${TEST_SOURCES} ${PROJECT_SOURCES})

# Link the required libraries
target_link_libraries(
  ${PROJECT_NAME}
  GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

# Set the include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Set the output directory for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../../bin")
