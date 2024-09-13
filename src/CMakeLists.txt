cmake_minimum_required(VERSION 3.30)
project(resonance LANGUAGES CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SOUNDIO REQUIRED IMPORTED_TARGET soundio)

add_executable(${PROJECT_NAME} main.cpp)
add_subdirectory(model)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SOUNDIO_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${SOUNDIO_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE ${SOUNDIO_CFLAGS_OTHER})
