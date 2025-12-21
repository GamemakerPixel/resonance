FetchContent_Declare(
	soundio
	GIT_REPOSITORY https://github.com/GamemakerPixel/libsoundio.git
	GIT_TAG a13b8c0b1e90d23f516828eef7fafca6c23c29ba
)

set(BUILD_DYNAMIC_LIBS OFF CACHE BOOL "")
set(BUILD_EXAMPLE_PROGRAMS OFF CACHE BOOL "")
set(BUILD_TESTS OFF CACHE BOOL "")

FetchContent_MakeAvailable(soundio)

add_library(${PROJECT_NAME}_soundio_backends STATIC)
target_include_directories(${PROJECT_NAME}_soundio_backends PUBLIC include)
target_link_libraries(${PROJECT_NAME}_soundio_backends PRIVATE libsoundio_static)
target_link_libraries(${PROJECT_NAME}_soundio_backends PRIVATE ${PROJECT_NAME}_core)
add_subdirectory(src)
