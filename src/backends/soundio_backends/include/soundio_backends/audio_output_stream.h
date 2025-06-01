#pragma once

#include <memory>

#include <soundio/soundio.h>

#include "core/audio_channel_layout.h"
#include "core/audio_data_type.h"
#include "core/audio_output_stream.h"

#include "soundio_backends/audio_interface_spec_soundio.h"


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
