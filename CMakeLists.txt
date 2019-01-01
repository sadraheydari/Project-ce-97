cmake_minimum_required(VERSION 3.0)
project(Phase1 C)
set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SOURCE "src/*.c" "src/*.h")
add_executable(Phase1 "${SOURCE}" src/Structs.h src/Graph.h src/HandleEvent.h src/Logic.h src/Move.h)

include_directories("/usr/include/SDL2")
target_link_libraries(Phase1 m SDL2 SDL2_gfx)
