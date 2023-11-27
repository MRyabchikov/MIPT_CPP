cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra")

cmake_path(SET LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}./lib")

include_directories (${LIB_DIR})

add_compile_definitions(WIN32)

add_subdirectory("SeminarsWork/class5/calculator")
#add_subdirectory("SeminarsWork/class6/vector")
#add_subdirectory("SeminarsWork/class6/logic_gate")
add_subdirectory("SeminarsWork/class9/shape_primitives")
add_subdirectory("SeminarsWork/class10/fractals")
add_subdirectory("SeminarsWork/class11/canvas")
add_subdirectory("SeminarsWork/class12/hexagon")
add_subdirectory("SeminarsWork/class14/least_squares")
add_subdirectory("SeminarsWork/class15/board")
add_subdirectory("Projects/Chess")
add_subdirectory("Projects/Vector")