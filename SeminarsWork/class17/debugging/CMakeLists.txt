set(TARGET "debugging")

project(${TARGET} LANGUAGES CXX)
add_executable(
                ${TARGET}
                debugging.cpp
                ${LIB_DIR}/tracer/tracer.cpp
                )
add_definitions(-DENABLE_TRACING)
install(TARGETS ${TARGET})