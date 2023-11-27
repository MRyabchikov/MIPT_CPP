set(TARGET "Vector")

project(${TARGET} LANGUAGES CXX)
add_executable(
                ${TARGET}
                main.cpp
                vector.cpp)
install(TARGETS ${TARGET})