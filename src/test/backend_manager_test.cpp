#include <gtest/gtest.h>
#include "core/backend_manager.h"

#include <memory>
#include <string>
#include <unordered_set>

#include "core/backend_factory.h"

#include "mock_backends/audio_backend.h"

using namespace resonance_core;


using BackendConstructor =
  std::function<std::unique_ptr<mock_backends::AudioBackend>()>;


static BackendConstructor
  make_constructor(int id, int device_count)
{
  return [id, device_count]()
  {
    return std::make_unique<mock_backends::AudioBackend>(id, device_count);
  };
}


class BackendManagerTest : public testing::Test
{
protected:
  std::unique_ptr<BackendManager> m_manager;

protected:
  BackendManagerTest()
  {
    std::unique_ptr<BackendFactory> factory = std::make_unique<BackendFactory>();

    const int backend_count = 3;
    const std::string backend_prefix = "Mock Backend ";
    const int device_count = 3;

    for (int backend_index = 0; backend_index < backend_count; backend_index++)
    {
      const std::string backend_name = backend_prefix + std::to_string(backend_index);

      factory->register_backend(
        backend_name,
        make_constructor(backend_index, device_count)
      );
    }

    m_manager = std::make_unique<BackendManager>(std::move(factory));
  }
};


TEST_F(BackendManagerTest, ReturnsBackendNames)
{
  const std::unordered_set<std::string> expected_names = {
    "Mock Backend 0", "Mock Backend 1", "Mock Backend 2"
  };

  const std::unordered_set<std::string> actual_names = m_manager->get_backend_names();

  EXPECT_EQ(expected_names, actual_names);
}


TEST_F(BackendManagerTest, ReturnsOutputDeviceNamesForExistingBackend)
{
  const std::unordered_set<std::string> expected_names = {
    "Mock Device 0-0", "Mock Device 0-1", "Mock Device 0-2"
  };

  const std::unordered_set<std::string> actual_names =
    m_manager->get_output_device_names("Mock Backend 0");

  EXPECT_EQ(expected_names, actual_names);
}


TEST_F(BackendManagerTest, ThrowsInvalidBackendNameOnNonExistantBackendDeviceQuery)
{
  EXPECT_THROW(
    m_manager->get_output_device_names("NonExistantBackend"),
    InvalidBackendNameException
  );
}
