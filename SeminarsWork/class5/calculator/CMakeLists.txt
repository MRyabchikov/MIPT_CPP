set(TARGET "calculator")

project(${TARGET} LANGUAGES CXX)
add_executable(
                ${TARGET}
                calculator08.cpp
                token.cpp
                symbol_table.cpp)
install(TARGETS ${TARGET})