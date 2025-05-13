#include <gtest/gtest.h>
#include "core/backend_loader.h"

#include <memory>
#include <string>
#include <unordered_set>

#include "core/backend_factory.h"

#include "mock_backends/audio_backend.h"

#include <iostream>

using namespace resonance_core;


using BackendConstructor =
  std::function<std::unique_ptr<mock_backends::AudioBackend>()>;

using CoreBackendPtr = std::shared_ptr<AudioBackend>;
using MockBackendPtr = std::shared_ptr<mock_backends::AudioBackend>;


static BackendConstructor
  make_constructor(int id, int device_count)
{
  return [id, device_count]()
  {
    return std::make_unique<mock_backends::AudioBackend>(id, device_count);
  };
}


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
        make_constructor(backend_index, device_count)
      );
    }

    m_loader = std::make_unique<BackendLoader>(factory);
  }
};


TEST_F(BackendLoaderTest, ReturnsInstanceOfRequestedBackend)
{
  MockBackendPtr backend = std::static_pointer_cast<mock_backends::AudioBackend>(
    m_loader->load_backend("Mock Backend 2")
  );

  EXPECT_EQ(2, backend->get_id());
}


TEST_F(BackendLoaderTest, ReusesBackendPointerWhenItIsAlive)
{
  const std::string backend_name = "Mock Backend 2";

  MockBackendPtr expected_backend =
    std::static_pointer_cast<mock_backends::AudioBackend>(
      m_loader->load_backend(backend_name));

  MockBackendPtr recieved_backend =
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
    MockBackendPtr first_backend =
      std::static_pointer_cast<mock_backends::AudioBackend>(
        m_loader->load_backend(backend_name));

    first_backend_instance_id = first_backend->get_unique_instance_id();
  }

  MockBackendPtr recieved_backend =
    std::static_pointer_cast<mock_backends::AudioBackend>(
      m_loader->load_backend(backend_name));

  EXPECT_NE(first_backend_instance_id, recieved_backend->get_unique_instance_id());
}
