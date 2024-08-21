cmake_minimum_required(VERSION 3.30)
project(resonance)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SOUNDIO REQUIRED IMPORTED_TARGET soundio)
pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET gtkmm-4.0)

add_executable(${PROJECT_NAME} main.cpp)
#target_sources()
target_link_libraries(${PROJECT_NAME} PRIVATE ${SOUNDIO_LIBRARIES} ${GTKMM_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${SOUNDIO_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE ${SOUNDIO_CFLAGS_OTHER} ${GTKMM_CFLAGS_OTHER})
