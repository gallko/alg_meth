set(BINARY_NAME_TEST ${BINARY_NAME}_test)

#file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

file(GLOB TEST_SOURCES
        ./main.cpp
        ./src/*.cpp)
include_directories(resources)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY_NAME_TEST} ${TEST_SOURCES})

add_test(NAME ${BINARY_NAME_TEST} COMMAND ${BINARY_NAME_TEST})

target_link_libraries(${BINARY_NAME_TEST} PUBLIC ${BINARY_NAME}_lib gtest)