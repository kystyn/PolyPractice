cmake_minimum_required(VERSION 3.8)

project(train LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(train main.cpp weather.h brake.h tools.h
    map_table.h train.h train.cpp brake.cpp stretch.cpp stretch.h
    optcontrolproblem.cpp optcontrolproblem.h
    solution.cpp solution.h
    abstractsolutiongenerator.cpp abstractsolutiongenerator.h
    differentialevolution.cpp differentialevolution.h)
