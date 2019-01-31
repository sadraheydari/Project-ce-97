cmake_minimum_required(VERSION 3.0)
project(AlterTank C)
set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SOURCE "src/*.c" "src/*.h")
add_executable(AlterTank "${SOURCE}" src/Structs.h src/Graph.h src/HandleEvent.h src/Logic.h src/Move.h src/SelectKeyboard.h)

include_directories("/usr/include/SDL2")
target_link_libraries(AlterTank m SDL2 SDL2_gfx)