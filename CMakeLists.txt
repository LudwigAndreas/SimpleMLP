cmake_minimum_required(VERSION 3.21)
project(SimpleMLP)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(SimpleMLP
        src/main.cpp
        src/Matrix.cpp
        src/Matrix.hpp src/MLPMatrixModel.cpp src/MLPMatrixModel.hpp)
