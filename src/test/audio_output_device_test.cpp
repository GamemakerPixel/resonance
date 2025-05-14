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
