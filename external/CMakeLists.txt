set(CMAKE_CXX_STANDARD_REQUIRED FALSE)

add_subdirectory(googletest)

set(BUILD_DYNAMIC_LIBS OFF)
set(BUILD_EXAMPLE_PROGRAMS OFF)
set(BUILD_TESTS OFF)
add_subdirectory(soundio)
