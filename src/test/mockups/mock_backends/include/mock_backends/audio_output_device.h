#pragma once

#include <memory>

#include "core/audio_output_device.h"


namespace mock_backends
{

class AudioBackend;

class AudioOutputDevice: public resonance_core::AudioOutputDevice
{
public:
  AudioOutputDevice(std::shared_ptr<AudioBackend> backend);
};

}
