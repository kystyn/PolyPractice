cmake_minimum_required(VERSION 3.8)

project(train LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(train main.cpp train.cpp brake.cpp stretch.cpp
    optcontrolproblem.cpp
    solution.cpp
    abstractsolutiongenerator.cpp
    differentialevolution.cpp
    simulator.cpp)
