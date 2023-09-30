set(TARGET "vector")

project(${TARGET} LANGUAGES CXX)
add_executable(
                ${TARGET}
                vector2d.cpp
                main.cpp
                )
install(TARGETS ${TARGET})