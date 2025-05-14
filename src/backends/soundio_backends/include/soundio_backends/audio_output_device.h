#pragma once

#include "core/audio_output_device.h"

#include <cstdint>
#include <memory>

#include <soundio/soundio.h>


namespace resonance_core
{

class AudioOutputDeviceSoundIo
{
private:
  const std::shared_ptr<const AudioBackendSoundIo> m_backend;
  const std::unique_ptr<const SoundIoDevice, void(*)(SoundIoDevice*)> m_device;

public:
  AudioOutputDeviceSoundIo(int device_index);

  std::unique_ptr<AudioOutputStream>
    get_stream() override;
  
  std::size_t
    get_backend_relative_hash() override;
};

}
