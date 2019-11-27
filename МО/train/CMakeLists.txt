cmake_minimum_required(VERSION 3.5)

project(train LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(train main.cpp weather.h brake.h map_table.h train.h train.cpp brake.cpp)
