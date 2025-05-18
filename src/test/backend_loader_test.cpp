#include <gtest/gtest.h>
#include "core/backend_loader.h"

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "core/backend_factory.h"

#include "mock_backends/audio_backend.h"
#include "mock_backends/audio_output_device.h"

#include "test_helpers.h"

using namespace resonance_core;


class BackendLoaderTest: public testing::Test
{
protected:
  std::unique_ptr<BackendLoader> m_loader;

protected:
  BackendLoaderTest()
  {
    std::shared_ptr<BackendFactory> factory = std::make_shared<BackendFactory>();

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

    m_loader = std::make_unique<BackendLoader>(factory);
  }
};


TEST_F(BackendLoaderTest, ReturnsInstanceOfRequestedBackend)
{
  test_help::MockBackendSPtr backend = std::static_pointer_cast<mock_backends::AudioBackend>(
    m_loader->load_backend("Mock Backend 2")
  );

  EXPECT_EQ(2, backend->get_id());
}


TEST_F(BackendLoaderTest, ReusesBackendPointerWhenItIsAlive)
{
  const std::string backend_name = "Mock Backend 2";

  test_help::MockBackendSPtr expected_backend =
    std::static_pointer_cast<mock_backends::AudioBackend>(
      m_loader->load_backend(backend_name));

  test_help::MockBackendSPtr recieved_backend =
    std::static_pointer_cast<mock_backends::AudioBackend>(
      m_loader->load_backend(backend_name));

  EXPECT_EQ(
    expected_backend->get_unique_instance_id(),
    recieved_backend->get_unique_instance_id()
  );
}


TEST_F(BackendLoaderTest, MakesNewBackendInstanceWhenOriginalIsDead)
{
  const std::string backend_name = "Mock Backend 2";

  int first_backend_instance_id;

  {
    test_help::MockBackendSPtr first_backend =
      std::static_pointer_cast<mock_backends::AudioBackend>(
        m_loader->load_backend(backend_name));

    first_backend_instance_id = first_backend->get_unique_instance_id();
  }

  test_help::MockBackendSPtr recieved_backend =
    std::static_pointer_cast<mock_backends::AudioBackend>(
      m_loader->load_backend(backend_name));

  EXPECT_NE(first_backend_instance_id, recieved_backend->get_unique_instance_id());
}


TEST_F(BackendLoaderTest, ReturnsInstanceOfRequestedDevice)
{
  test_help::MockOutputDeviceSPtr device = std::static_pointer_cast<
    mock_backends::AudioOutputDevice
  >(m_loader->load_device("Mock Backend 1", "Mock Device 1-1"));

  EXPECT_EQ(std::make_pair(1, 1), device->get_id());
}
