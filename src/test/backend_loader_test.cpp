#include <gtest/gtest.h>
#include "core/core.h"

#include <memory>
#include <string>
#include <utility>

#include "mock_backends/mock_backends.h"

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


TEST_F(BackendLoaderTest, ReturnsInstanceOfRequestedOutputDevice)
{
  test_help::MockOutputDeviceSPtr device = std::static_pointer_cast<
    mock_backends::AudioOutputDevice
  >(m_loader->load_output_device("Mock Backend 1", "Mock Device 1-1"));

  EXPECT_EQ(std::make_pair(1, 1), device->get_id());
}


TEST_F(BackendLoaderTest, ReusesOutputDevicePointerWhenItIsAlive)
{
  const std::string backend_name = "Mock Backend 2";
  const std::string device_name = "Mock Device 2-0";

  test_help::MockOutputDeviceSPtr expected_device =
    std::static_pointer_cast<mock_backends::AudioOutputDevice>(
      m_loader->load_output_device(backend_name, device_name));

  test_help::MockOutputDeviceSPtr recieved_device =
    std::static_pointer_cast<mock_backends::AudioOutputDevice>(
      m_loader->load_output_device(backend_name, device_name));

  EXPECT_EQ(
    expected_device->get_unique_instance_id(),
    recieved_device->get_unique_instance_id()
  );
}


TEST_F(BackendLoaderTest, MakesNewOutputDeviceInstanceWhenOriginalIsDead)
{
  const std::string backend_name = "Mock Backend 2";
  const std::string device_name = "Mock Device 2-0";

  int first_device_instance_id;

  {
    test_help::MockOutputDeviceSPtr first_device =
      std::static_pointer_cast<mock_backends::AudioOutputDevice>(
        m_loader->load_output_device(backend_name, device_name));

    first_device_instance_id = first_device->get_unique_instance_id();
  }

  test_help::MockOutputDeviceSPtr recieved_device =
    std::static_pointer_cast<mock_backends::AudioOutputDevice>(
      m_loader->load_output_device(backend_name, device_name));

  EXPECT_NE(first_device_instance_id, recieved_device->get_unique_instance_id());
}


TEST_F(BackendLoaderTest, DeviceKeepsBackendInstanceAlive)
{
  const std::string backend_name = "Mock Backend 2";
  const std::string device_name = "Mock Device 2-0";

  int first_backend_instance_id;
  test_help::CoreOutputDeviceSPtr device;

  {
    test_help::MockBackendSPtr first_backend =
      std::static_pointer_cast<mock_backends::AudioBackend>(
        m_loader->load_backend(backend_name));

    first_backend_instance_id = first_backend->get_unique_instance_id();

    device = m_loader->load_output_device(backend_name, device_name);
  }

  test_help::MockBackendSPtr recieved_backend =
    std::static_pointer_cast<mock_backends::AudioBackend>(
      m_loader->load_backend(backend_name));

  EXPECT_EQ(first_backend_instance_id, recieved_backend->get_unique_instance_id());
}


TEST_F(BackendLoaderTest, ReturnsInstanceOfRequestedOutputStream)
{
  const AudioInterfaceSpec spec(
    AudioDataType::FLOAT32,
    standard_layouts::stereo,
    44100u
  );

  test_help::MockOutputStreamUPtr stream = test_help::cast_to_mocked_stream(
    m_loader->create_output_stream("Mock Backend 1", "Mock Device 1-1", spec)
  );

  EXPECT_EQ(std::make_pair(1, 1), stream->get_device_id());
}


TEST_F(BackendLoaderTest, StreamKeepsDeviceInstanceAlive)
{
  const std::string backend_name = "Mock Backend 2";
  const std::string device_name = "Mock Device 2-0";
  const AudioInterfaceSpec spec(
    AudioDataType::FLOAT32,
    standard_layouts::stereo,
    44100u
  );

  int first_device_instance_id;
  test_help::CoreOutputStreamUPtr stream;

  {
    test_help::MockOutputDeviceSPtr first_device =
      std::static_pointer_cast<mock_backends::AudioOutputDevice>(
        m_loader->load_output_device(backend_name, device_name));

    first_device_instance_id = first_device->get_unique_instance_id();

    stream = m_loader->create_output_stream(backend_name, device_name, spec);
  }

  test_help::MockOutputDeviceSPtr recieved_device=
    std::static_pointer_cast<mock_backends::AudioOutputDevice>(
      m_loader->load_output_device(backend_name, device_name));

  EXPECT_EQ(first_device_instance_id, recieved_device->get_unique_instance_id());
}
