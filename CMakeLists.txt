cmake_minimum_required(VERSION 3.0)

project(hello-vsc)

set(SOURCE main.cpp lesson_6.1.h)

add_executable(hello-vsc ${SOURCE})

set_target_properties(hello-vsc PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
