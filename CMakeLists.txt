cmake_minimum_required(VERSION 3.31)
project(
  resonance
  VERSION 1.0
  LANGUAGES CXX
)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(CTest)

add_subdirectory(external)
add_subdirectory(src)
