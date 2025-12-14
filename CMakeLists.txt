cmake_minimum_required(VERSION 4.1)
project(deadfish_interpreter C)

set(CMAKE_C_STANDARD 23)

add_executable(deadfish_interpreter main.c)
target_link_libraries(deadfish_interpreter m)
