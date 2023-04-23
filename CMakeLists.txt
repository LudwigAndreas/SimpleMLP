cmake_minimum_required(VERSION 3.20)
project(SimpleMLP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(src)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Ofast ")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -g -Og")
set(CMAKE_CXX_FLAGS_RELEASE  "-Ofast -march=native")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(Libs21_dir "${CMAKE_SOURCE_DIR}/libs21/")
link_directories(${Libs21_dir}/build/src)

set(CMAKE_PREFIX_PATH "~/Qt/6.4.3/macos/lib/cmake/")
find_package(Qt6 ${PROJECT_VERSION} CONFIG OPTIONAL_COMPONENTS Gui Widgets Charts) # special case
qt_standard_project_setup()

add_executable(SimpleMLP
        src/core/utils/ActivationFunction.cpp
        src/core/DatasetReading.cpp
        src/core/LetterRecognitionMlpModelBuilder.cpp
        src/core/graph/MLPGraphLayer.cpp
        src/core/graph/MLPGraphModel.cpp
        src/core/graph/MLPGraphNode.cpp
#        src/core/main.cpp


        src/gui/main.cpp
        src/gui/view/ConfigureModulePage.cpp
        src/gui/view/TrainModelPage.cpp
        src/gui/view/TestModelPage.cpp
        src/gui/utils/importfileitem.cpp
        src/gui/view/mainwindow.cpp
        src/gui/utils/paintview.cpp
        src/gui/view/testdatainfodialog.cpp
        src/gui/view/mainwindow.ui
        src/gui/view/testdatainfodialog.ui
        src/gui/resourses.qrc
        src/gui/utils/ModelTestWorker.cpp
        src/gui/utils/ModelTrainWorker.cpp
        src/gui/utils/ModelWorker.cpp
        src/tests/core/graph/GraphTest.cc
        src/tests/core/graph/GraphModelTest.cc
        src/tests/core/matrix/MatrixModelTest.cc
        src/tests/core/graph/GraphLayerTest.cc
        src/tests/core/DatasetReadingTest.cc
        src/tests/core/MLPBuilderTest.cc
        src/core/exceptions/UploadFileException.h
        src/core/matrix/MLPMatrixModel.cc
        )
target_link_libraries(SimpleMLP Qt6::Widgets Qt6::Charts ${GTEST_BOTH_LIBRARIES})
#target_link_libraries(SimpleMLP ${GTEST_BOTH_LIBRARIES})
