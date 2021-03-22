#CMakeLists.txt
cmake_minimum_required (VERSION 3.6)
project(reki)

add_executable(reki src/reki.cpp)

add_subdirectory(deps/sleepy-discord)
target_link_libraries(reki sleepy-discord)
