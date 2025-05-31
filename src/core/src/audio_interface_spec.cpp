#include "core/audio_interface_spec.h"

using namespace resonance_core;


AudioInterfaceSpec::AudioInterfaceSpec(
  AudioDataType data_type,
  AudioChannelLayout layout,
  unsigned int sample_rate
): m_data_type(data_type), m_layout(layout), m_sample_rate(sample_rate) {}


bool
  AudioInterfaceSpec::operator==(const AudioInterfaceSpec& other) const
{
  return (
		m_data_type == other.m_data_type
    && m_layout == other.m_layout
    && m_sample_rate == other.m_sample_rate
  );
}


bool
  AudioInterfaceSpec::operator!=(const AudioInterfaceSpec& other) const
{
  return !operator==(other);
}
