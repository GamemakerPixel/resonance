#pragma once

#include "core/audio_channel_layout.h"
#include "core/audio_data_type.h"
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

private:
  static SoundIoFormat core_type_to_soundio_format(resonance_core::AudioDataType type);
  static SoundIoChannelLayout core_layout_to_soundio_layout(
    resonance_core::AudioChannelLayout layout
  );
  static SoundIoChannelId core_channel_id_to_soundio_channel_id(
    resonance_core::AudioChannelId id
  );
};

}
