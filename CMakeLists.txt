cmake_minimum_required(VERSION 3.21)
project(SimpleMLP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(src)

#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "-Wall -Wextra -g -Og")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -g -Og")
#set(CMAKE_CXX_FLAGS_RELEASE  "-Ofast -march=native")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()
find_package(Qt6Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(SimpleMLP
#        src/core/graph/MLPGraphLayer.hpp
#        src/core/graph/MLPGraphModel.hpp
#        src/core/graph/MLPGraphNode.hpp
#        src/core/matrix/Matrix.hpp
#        src/core/matrix/MLPMatrixModel.hpp
        src/core/utils/ActivationFunction.cpp
        src/core/utils/BMPReader.cpp
#        src/core/utils/BMPReader.hpp
#        src/core/exceptions/MatrixException.hpp
        src/core/DatasetReading.cpp
        src/core/LetterRecognitionMlpModelBuilder.cpp

        src/gui/main.cpp
        src/gui/utils/MTWorker.cpp
#        src/gui/utils/MTWorker.hpp
        src/gui/view/ConfigureModulePage.cpp
        src/gui/view/TrainModelPage.cpp
        src/gui/view/TestModelPage.cpp
#        src/gui/utils/importfileitem.h
        src/gui/utils/importfileitem.cpp
        src/gui/view/mainwindow.cpp
#        src/gui/view/mainwindow.h
        src/gui/utils/paintview.cpp
#        src/gui/utils/paintview.h
        src/gui/view/testdatainfodialog.cpp
#        src/gui/view/testdatainfodialog.h
        src/gui/view/mainwindow.ui
        src/gui/view/testdatainfodialog.ui
        src/gui/resourses.qrc
#        src/tests/main.cpp src/tests/core/matrix/MatrixTest.cpp
#        src/tests/core/utils/ActivationFunctionTest.cpp src/tests/core/utils/BMPReaderTest.cpp
        )
target_link_libraries(SimpleMLP Qt6::Widgets)
#target_link_libraries(SimpleMLP ${GTEST_BOTH_LIBRARIES})
