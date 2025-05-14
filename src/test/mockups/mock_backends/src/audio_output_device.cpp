#include "mock_backends/audio_output_device.h"

#include <memory>

#include "core/audio_output_device.h"

#include "mock_backends/audio_backend.h"

using namespace mock_backends;


AudioOutputDevice::AudioOutputDevice(std::shared_ptr<AudioBackend> backend)
  : resonance_core::AudioOutputDevice(backend) {}
