
cmake_minimum_required (VERSION 3.8)

project(ApplicationGUI VERSION 1.0.0)

message(STATUS "Path is ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(ApplicationGUI STATIC "MainWindow.cpp" "MainWindow.h")

target_include_directories(ApplicationGUI PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

#target_compile_definitions(ApplicationGUI PUBLIC ApplicationGUI_VERSION=8)