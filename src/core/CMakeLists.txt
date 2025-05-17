add_library(${PROJECT_NAME}_core STATIC)
target_include_directories(${PROJECT_NAME}_core PUBLIC include)
add_subdirectory(src)
