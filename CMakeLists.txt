cmake_minimum_required(VERSION 3.20)
project(bchess)

add_executable(bchess bchess.cpp)
target_link_libraries(bchess SDL2)