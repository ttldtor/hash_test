cmake_minimum_required(VERSION 3.15)
project(hash_test)

set(CMAKE_CXX_STANDARD 17)

add_executable(hash_test main.cpp)
add_custom_command(TARGET hash_test POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/symbols.txt ${CMAKE_BINARY_DIR}/symbols.txt)