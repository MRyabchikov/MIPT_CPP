set(TARGET "logic_gate")

project(${TARGET} LANGUAGES CXX)
add_executable(
                ${TARGET}
                logic_gate.cpp
                main.cpp
                )
install(TARGETS ${TARGET})