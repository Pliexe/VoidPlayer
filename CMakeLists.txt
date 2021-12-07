# CMakeList.txt : Top-level CMake project file, do global configuration
# DZ


cmake_minimum_required (VERSION 3.8)

project (VoidPlayer VERSION 1.0.0)

set(CXX_STANDARD  17)
set(CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/VoidPlayer)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/VoidPlayer)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

# Include sub-projects.
add_subdirectory ("BASS")
add_subdirectory ("ApplicationGUI")
add_subdirectory ("MusicHandler")

add_subdirectory ("VoidPlayerCore")
