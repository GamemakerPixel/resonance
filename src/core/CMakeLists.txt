add_library(${PROJECT_NAME}_core STATIC)
target_include_directories(${PROJECT_NAME}_core PUBLIC include)
target_link_libraries(${PROJECT_NAME}_core soundio)
add_subdirectory(src)
