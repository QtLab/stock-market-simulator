cmake_minimum_required(VERSION 2.8.11)
project(stock-market-simulator)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to inspect C++ to determine if they require uic to be run
set(CMAKE_AUTOUIC ON)

# Instruct CMake to execute rcc on source files which have the suffix .qrc
set(CMAKE_AUTORCC ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Compiler Options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall -Wextra -Werror -fPIC")

# Find the Qt library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

add_subdirectory(gui)

# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${PROJECT_SOURCE_DIR}/gui/include
                    ${CMAKE_BINARY_DIR}/gui
                    ${Qt5Widgets_INCLUDE_DIRS}
                    ${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Gui_INCLUDE_DIRS})

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})

# Executables fail to build with Qt 5 in the default configuration
# without -fPIE. We add that here.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

set( PROJECT_SOURCES src/present_value.cpp)
add_library(sources ${PROJECT_SOURCES})

add_executable(       ${PROJECT_NAME} src/main.cpp)
add_dependencies(     ${PROJECT_NAME} sources)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets gui sources)
