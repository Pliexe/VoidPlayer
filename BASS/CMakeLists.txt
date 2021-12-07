
cmake_minimum_required (VERSION 3.8)

project(bass)

message("bass location: ${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_library(bass SHARED "bass.dll" "bass.lib" "bass.h")
set_target_properties(bass PROPERTIES LINKER_LANGUAGE C)

install(TARGETS bass)