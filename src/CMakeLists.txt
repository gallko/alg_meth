
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

add_executable(${BINARY_NAME} ${SOURCES})

add_library(${BINARY_NAME}_lib STATIC ${SOURCES})

target_compile_options(${BINARY_NAME} PRIVATE -Wall)
