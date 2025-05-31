if (BUILD_TESTING)
  add_subdirectory(mockups)

  add_executable(${PROJECT_NAME}_tests)
  target_link_libraries(${PROJECT_NAME}_tests PRIVATE GTest::gtest_main)
  target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME}_core)
  target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME}_tests_mock_backends)
  target_sources(${PROJECT_NAME}_tests PRIVATE
    abstract_depender_test.cpp
    abstract_subscription_ptr_test.cpp
		audio_channel_layout_test.cpp
		audio_data_type_test.cpp
		audio_interface_spec_test.cpp
    backend_factory_test.cpp
    backend_loader_test.cpp
    backend_manager_test.cpp
  )

  include(GoogleTest)
  gtest_discover_tests(${PROJECT_NAME}_tests)
endif()
