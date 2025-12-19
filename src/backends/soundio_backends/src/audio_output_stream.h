#pragma once

#include <memory>

#include <soundio/soundio.h>

#include "core/core.h"

#include "audio_interface_spec_soundio.h"


namespace soundio_backends
{

class AudioOutputStream: public resonance_core::AudioOutputStream
{
private:
  std::unique_ptr<SoundIoOutStream, void(*)(SoundIoOutStream*)> m_stream;

public:
  AudioOutputStream(
    std::unique_ptr<SoundIoOutStream, void(*)(SoundIoOutStream*)> stream,
    const AudioInterfaceSpecSoundIo& spec
  );
};

}
