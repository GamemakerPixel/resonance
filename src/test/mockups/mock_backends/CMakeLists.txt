add_library(${PROJECT_NAME}_tests_mock_backends STATIC)
target_include_directories(${PROJECT_NAME}_tests_mock_backends PUBLIC include)
target_link_libraries(${PROJECT_NAME}_tests_mock_backends ${PROJECT_NAME}_core)
add_subdirectory(src)
