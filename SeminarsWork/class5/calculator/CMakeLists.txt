set(TARGET "calculator")

project(${TARGET} LANGUAGES CXX)
add_executable(
                ${TARGET}
                calculator08.cpp
                token.cpp
                variable.cpp)
install(TARGETS ${TARGET})