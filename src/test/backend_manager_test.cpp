#include <gtest/gtest.h>
#include "core/audio_backend.h"
#include "core/audio_channel_layout.h"
#include "core/audio_data_type.h"
#include "core/audio_interface_spec.h"
#include "core/backend_manager.h"

#include <memory>
#include <string>
#include <unordered_set>

#include "core/backend_factory.h"

#include "test_helpers.h"

using namespace resonance_core;


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
        test_help::make_constructor(backend_index, device_count)
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


TEST_F(BackendManagerTest, ReturnsOutputStream)
{
  const std::string backend = "Mock Backend 0";
  const std::string device = "Mock Device 0-0";
  const AudioInterfaceSpec spec(
    AudioDataType::FLOAT32,
    standard_layouts::stereo,
    44100u
  );

  const test_help::MockOutputStreamUPtr stream = test_help::cast_to_mocked_stream(
    m_manager->get_stream(backend, device, spec)
  );

  EXPECT_EQ(std::make_pair(0, 0), stream->get_device_id());
}


// You could reasonably argue this test shouldn't exist because it depends on the mockup
// implementation, but I would argue this makes sense as it documents that 
// BackendManager will not handle these errors when they are thrown.
TEST_F(BackendManagerTest, ForwardsInvalidBackendNameOnNonExistantBackendDeviceQuery)
{
  EXPECT_THROW(
    m_manager->get_output_device_names("NonExistantBackend"),
    InvalidBackendNameException
  );
}


TEST_F(BackendManagerTest, ForwardsInvalidBackendNameOnNonExistantBackendStreamCreation)
{
  const std::string backend = "NonExistantBackend";
  const std::string device = "Mock Device 0-0";
  const AudioInterfaceSpec spec(
    AudioDataType::FLOAT32,
    standard_layouts::stereo,
    44100u
  );

  EXPECT_THROW(
    m_manager->get_stream(backend, device, spec),
    InvalidBackendNameException
  );
}


TEST_F(BackendManagerTest, ForwardsDeviceNotAvaliableOnNonExistantDeviceStreamCreation)
{
  const std::string backend = "Mock Backend 0";
  const std::string device = "NonExistantDevice";
  const AudioInterfaceSpec spec(
    AudioDataType::FLOAT32,
    standard_layouts::stereo,
    44100u
  );

  EXPECT_THROW(
    m_manager->get_stream(backend, device, spec),
    DeviceNotAvaliableException
  );
}
