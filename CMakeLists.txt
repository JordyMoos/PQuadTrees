
cmake_minimum_required(VERSION 3.4)
project(PQuadTrees)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories( ./dependencies/php5/main ./dependencies/php5/Zend )

set(SOURCE_FILES main.cpp )
add_executable(PQuadTrees ${SOURCE_FILES})
