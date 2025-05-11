if (BUILD_TESTING)
  

  add_executable(${PROJECT_NAME}_tests)
  target_link_libraries(${PROJECT_NAME}_tests PRIVATE GTest::gtest_main)
  target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME}_core)
  add_subdirectory(mockups) # Links mockup libraries
  target_sources(${PROJECT_NAME}_tests PRIVATE
    backend_factory_test.cpp
  )

  include(GoogleTest)
  gtest_discover_tests(${PROJECT_NAME}_tests)
endif()
