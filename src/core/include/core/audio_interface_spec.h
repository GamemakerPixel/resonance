#pragma once

#include "core/audio_channel_layout.h"
#include "core/audio_data_type.h"


namespace resonance_core
{

struct AudioInterfaceSpec
{
  AudioDataType m_data_type;
  AudioChannelLayout m_layout;
  unsigned int m_sample_rate;

  AudioInterfaceSpec(
    AudioDataType data_type,
    AudioChannelLayout layout,
    unsigned int sample_rate
  ) : m_data_type(data_type), m_layout(layout), m_sample_rate(sample_rate) {}
};

}
