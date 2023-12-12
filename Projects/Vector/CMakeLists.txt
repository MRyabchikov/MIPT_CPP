set(TARGET "Vector")

project(${TARGET} LANGUAGES CXX)
add_executable(
                ${TARGET}
                main.cpp
                #vector.cpp
                ${LIB_DIR}/tracer/tracer.cpp
                )
add_definitions(-DENABLE_TRACING)
install(TARGETS ${TARGET})