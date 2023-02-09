cmake_minimum_required(VERSION 3.21)
project(SimpleMLP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(src)
set(CMAKE_PREFIX_PATH "~/Qt/6.4.2/macos/lib/cmake")
find_package(Qt6Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(SimpleMLP
        src/core/ActivationFunction.cpp
        src/core/ActivationFunction.hpp
        src/core/IMLPModel.hpp
#        src/core/main.cpp
        src/core/Matrix.hpp
        src/core/MLPMatrixModel.hpp
        src/core/MLPMatrixModelv2.hpp
        src/core/MLPSerializer.hpp
        src/core/Sample.hpp

        src/gui/main.cpp
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
        )
target_link_libraries(SimpleMLP Qt6::Widgets)