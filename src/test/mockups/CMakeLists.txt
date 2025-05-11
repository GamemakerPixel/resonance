add_subdirectory(mock_backends)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME}_tests_mock_backends)
