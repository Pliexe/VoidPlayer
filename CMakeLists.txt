# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (VoidPlayer VERSION 1.0.0)

# Include sub-projects.
add_subdirectory ("ApplicationGUI")
add_subdirectory ("VoidPlayerCore")
