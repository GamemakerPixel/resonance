cmake_minimum_required(VERSION 3.30)
project(resonance LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

add_subdirectory(core)
add_subdirectory(backends)
add_subdirectory(views)
add_subdirectory(test)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_core)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_soundio_backends)
