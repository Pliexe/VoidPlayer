
cmake_minimum_required (VERSION 3.8)

project(VoidPlayerCore)

add_executable (VoidPlayerCore WIN32 "Void Player.cpp" "Void Player.h")

target_compile_features(VoidPlayerCore PUBLIC cxx_std_17)

#target_link_directories(VoidPlayerCore PRIVATE ApplicationGUI)

include_directories("../ApplicationGUI/")

target_link_libraries(VoidPlayerCore ApplicationGUI)
