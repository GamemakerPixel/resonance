#pragma once

#include "core/audio_output_device.h"

#include <memory>

#include <soundio/soundio.h>


namespace soundio_backends
{

class AudioOutputDevice: public resonance_core::AudioOutputDevice
{
private:
  const std::unique_ptr<SoundIoDevice, void(*)(SoundIoDevice*)> m_device;

public:
  AudioOutputDevice(std::unique_ptr<SoundIoDevice, void(*)(SoundIoDevice*)> device);

  std::unique_ptr<resonance_core::AudioOutputStream>
    create_stream(const resonance_core::AudioInterfaceSpec& spec) const override;
  
  bool
    is_spec_compatable(const resonance_core::AudioInterfaceSpec& spec) const override;

private:
  void
    validate_spec(const resonance_core::AudioInterfaceSpec& spec) const;
    
  SoundIoFormat
    negotiate_compatable_format(resonance_core::AudioDataType type) const;
};

}
