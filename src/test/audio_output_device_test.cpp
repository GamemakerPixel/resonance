#include <gtest/gtest.h>
#include "core/audio_output_device.h"

#include <memory>
#include <string>

#include "core/audio_backend.h"

#include "mock_backends/audio_backend.h"
#include "mock_backends/audio_output_device.h"

#include "test_helpers.h"

using namespace resonance_core;


TEST(AudioOutputDeviceTest, KeepsOriginatingBackendAlive)
{
  test_help::MockOutputDeviceUPtr device;
  std::weak_ptr<mock_backends::AudioBackend> backend;

  {
    auto owned_backend = std::make_shared<mock_backends::AudioBackend>(0, 0);
    backend = owned_backend;

    device = std::make_unique<mock_backends::AudioOutputDevice>(owned_backend);
  }

  EXPECT_FALSE(backend.expired());
}

// All subclasses of AudioOutputDevice must keep an owning reference to the AudioBackend
// that created them (thus keeping the connection to the backend from closing while the
// device is in use), but since it would have to be passed through the concrete
// AudioOutputDevice's constructor, I cannot enforce that an AudioBackend will pass a
// reference of itself to the AudioOutputDevice, or that a concrete implementation of
// AudioOutputDevice will pass this reference to the abstract AudioOutputDevice
// constructor. The second best option is to enforce that an abstract AudioOutputDevice
// will throw an exception if it is created without a reference to an AudioBackend -
// hence this test.
TEST(AudioOutputDeviceTest, ThrowsNullBackendWhenCreatedWithNullBackend)
{
  test_help::MockBackendSPtr null_backend;

  EXPECT_THROW(
    std::make_unique<mock_backends::AudioOutputDevice>(null_backend),
    NullBackendException
  );
}
