
cmake_minimum_required (VERSION 3.8)

project(MusicHandler VERSION 1.0.0)

add_library(MusicHandler SHARED "MusicHandler.cpp" "MusicHandler.h")

target_link_directories(MusicHandler PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(MusicHandler PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

install(TARGETS MusicHandler)


#target_compile_definitions(ApplicationGUI PUBLIC ApplicationGUI_VERSION=8)