#pragma once

#include "core/audio_interface_spec.h"
#include "core/audio_output_stream.h"
#include <memory>
#include <soundio/soundio.h>


namespace soundio_backends
{

class AudioOutputStream: public resonance_core::AudioOutputStream
{
private:
  std::unique_ptr<SoundIoOutStream, void(*)(SoundIoOutStream*)> m_stream;

public:
  AudioOutputStream(
    std::unique_ptr<SoundIoOutStream, void(*)(SoundIoOutStream*)> stream,
    const resonance_core::AudioInterfaceSpec& spec
  );
};

}
