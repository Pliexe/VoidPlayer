
cmake_minimum_required (VERSION 3.8)

project(ApplicationGUI VERSION 1.0.0)

include_directories("../MusicHandler/")

add_library(ApplicationGUI SHARED "MainWindow.cpp" "MainWindow.h"  "BaseWindow.h" "ButtonControls.h" "Controls.h" "Panels/MusicControl.h" "GraphicsUtils.h")

target_link_libraries(ApplicationGUI MusicHandler)

target_link_directories(ApplicationGUI PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(ApplicationGUI PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

install(TARGETS ApplicationGUI)


#target_compile_definitions(ApplicationGUI PUBLIC ApplicationGUI_VERSION=8)