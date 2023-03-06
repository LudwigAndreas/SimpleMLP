cmake_minimum_required(VERSION 3.21)
project(SimpleMLP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(src)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "-Wall -Wextra -g -Og")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -g -Og")
#set(CMAKE_CXX_FLAGS_RELEASE  "-Ofast -march=native")

set(CMAKE_PREFIX_PATH "~/Qt/6.4.2/macos/lib/cmake")
find_package(Qt6Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(SimpleMLP
        src/core/utils/ActivationFunction.cpp
#        src/core/ActivationFunction.hpp
#        src/core/IMLPModel.hpp
        src/core/DatasetReading.cpp
        src/core/LetterRecognitionMlpModelBuilder.cpp
        #        src/core/matrix/Matrix.hpp
        #        src/core/MLPMatrixModel.hpp
        #        src/core/MLPMatrixModelv2.hpp
        #        src/core/MLPSerializer.hpp
        #        src/core/Sample.hpp
#        src/core/utils/BMPReader.cpp
#        src/core/main.cpp

#        src/gui/main.cpp
        src/gui/MTWorker.cpp
        src/gui/MTWorker.hpp
        src/gui/importfileitem.h
        src/gui/importfileitem.cpp
        src/gui/mainwindow.cpp
        src/gui/mainwindow.h
        src/gui/paintview.cpp
        src/gui/paintview.h
        src/gui/testdatainfodialog.cpp
        src/gui/testdatainfodialog.h
        src/gui/mainwindow.ui
        src/gui/testdatainfodialog.ui
        src/gui/resourses.qrc
        src/core/utils/BMPReader.cpp src/core/utils/BMPReader.hpp
        src/tests/main.cpp src/tests/core/matrix/MatrixTest.cpp src/core/exceptions/MatrixException.hpp)
target_link_libraries(SimpleMLP Qt6::Widgets)
target_link_libraries(SimpleMLP ${GTEST_BOTH_LIBRARIES})
