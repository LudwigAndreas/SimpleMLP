cmake_minimum_required(VERSION 3.20)
project(SimpleMLP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(src)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -g -Og")
set(CMAKE_CXX_FLAGS_RELEASE  "-Ofast -march=native")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -g -Og -Ofast -march=native")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()
find_package(Qt6Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH "~/Qt/6.4.3/macos/lib/cmake/")
find_package(Qt6 ${PROJECT_VERSION} CONFIG OPTIONAL_COMPONENTS Gui Widgets Charts) # special case
qt_standard_project_setup()

add_executable(SimpleMLP
        src/core/utils/ActivationFunction.cpp
#        src/core/graph/MLPGraphLayer.hpp
#        src/core/graph/MLPGraphModel.hpp
#        src/core/graph/MLPGraphNode.hpp
#        src/core/matrix/Matrix.hpp
        src/core/matrix/MLPMatrixLayer.cc
        src/core/matrix/MLPMatrixModel.cc
        src/core/utils/ActivationFunction.cpp
#        src/core/utils/BMPReader.cpp
#        src/core/utils/BMPReader.hpp
#        src/core/exceptions/MatrixException.hpp
        src/core/DatasetReading.cpp
        src/core/LetterRecognitionMlpModelBuilder.cpp
        src/core/graph/MLPGraphLayer.cpp
        src/core/graph/MLPGraphModel.cpp
        src/core/graph/MLPGraphNode.cpp
#        src/core/main.cpp


        src/gui/main.cpp
#        src/gui/utils/MTWorker.cpp
#        src/gui/utils/MTWorker.hpp
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
        src/gui/utils/ModelWorker.hpp
        src/core/utils/AFLibrary.cc
        )


# Import static library
add_library(libs21 STATIC IMPORTED)

# Set library location for each configuration
set_target_properties(libs21 PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/src/libs21/lib/libs21.a
        )

target_link_libraries(SimpleMLP Qt6::Widgets Qt6::Charts ${GTEST_BOTH_LIBRARIES} libs21)
#52b76022a37
#d78c35a04b