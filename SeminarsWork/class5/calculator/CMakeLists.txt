set(TARGET "calculator")

project(${TARGET} LANGUAGES CXX)
add_executable(
                ${TARGET}
                calculator08.cpp)
install(TARGETS ${TARGET})