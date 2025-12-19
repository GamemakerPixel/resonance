#include "audio_interface_spec_soundio.h"
#include "core/core.h"

#include <limits>
#include <soundio/soundio.h>
#include <string>

using namespace soundio_backends;


const std::unordered_map<
  resonance_core::AudioChannelId, SoundIoChannelId
> AudioInterfaceSpecSoundIo::channel_ids =
{
  {resonance_core::AudioChannelId::LEFT, SoundIoChannelIdFrontLeft},
  {resonance_core::AudioChannelId::RIGHT, SoundIoChannelIdFrontRight},
  {resonance_core::AudioChannelId::CENTER, SoundIoChannelIdFrontCenter},
  {resonance_core::AudioChannelId::LFE, SoundIoChannelIdLfe},
  {resonance_core::AudioChannelId::BACK_LEFT, SoundIoChannelIdBackLeft},
  {resonance_core::AudioChannelId::BACK_RIGHT, SoundIoChannelIdBackRight},
  {resonance_core::AudioChannelId::FRONT_LEFT_CENTER, SoundIoChannelIdFrontLeftCenter},
  {resonance_core::AudioChannelId::FRONT_RIGHT_CENTER, SoundIoChannelIdFrontRightCenter},
  {resonance_core::AudioChannelId::BACK_CENTER, SoundIoChannelIdBackCenter},
  {resonance_core::AudioChannelId::SIDE_LEFT, SoundIoChannelIdSideLeft},
  {resonance_core::AudioChannelId::SIDE_RIGHT, SoundIoChannelIdSideRight},
  {resonance_core::AudioChannelId::TOP_CENTER, SoundIoChannelIdTopCenter},
  {resonance_core::AudioChannelId::TOP_FRONT_LEFT, SoundIoChannelIdTopFrontLeft},
  {resonance_core::AudioChannelId::TOP_FRONT_CENTER, SoundIoChannelIdTopFrontCenter},
  {resonance_core::AudioChannelId::TOP_FRONT_RIGHT, SoundIoChannelIdTopFrontRight},
  {resonance_core::AudioChannelId::TOP_BACK_LEFT, SoundIoChannelIdTopBackLeft},
  {resonance_core::AudioChannelId::TOP_BACK_CENTER, SoundIoChannelIdTopBackCenter},
  {resonance_core::AudioChannelId::TOP_BACK_RIGHT, SoundIoChannelIdTopBackRight},
  {resonance_core::AudioChannelId::AUX, SoundIoChannelIdAux},
};


const std::unordered_map<
  resonance_core::AudioDataType, std::array<SoundIoFormat, 4>
> AudioInterfaceSpecSoundIo::formats =
{
  {resonance_core::AudioDataType::INT8,
    {{SoundIoFormatS8, SoundIoFormatU8, SoundIoFormatS8, SoundIoFormatU8}}
  },
  {resonance_core::AudioDataType::INT16,
    {{SoundIoFormatS16NE, SoundIoFormatU16NE, SoundIoFormatS16FE, SoundIoFormatU16FE}}
  },
  {resonance_core::AudioDataType::INT24,
    {{SoundIoFormatS24NE, SoundIoFormatU24NE, SoundIoFormatS24FE, SoundIoFormatU24FE}}
  },
  {resonance_core::AudioDataType::INT32,
    {{SoundIoFormatS32NE, SoundIoFormatU32NE, SoundIoFormatS32FE, SoundIoFormatU32FE}}
  },
  {resonance_core::AudioDataType::FLOAT32,
    {{
      SoundIoFormatFloat32NE, SoundIoFormatFloat32NE,
      SoundIoFormatFloat32FE, SoundIoFormatFloat32FE
    }}
  },
  {resonance_core::AudioDataType::FLOAT64,
    {{
      SoundIoFormatFloat64NE, SoundIoFormatFloat64NE,
      SoundIoFormatFloat64FE, SoundIoFormatFloat64FE
    }}
  },
};
  

const std::unordered_set<SoundIoFormat> AudioInterfaceSpecSoundIo::unsigned_formats =
{
  SoundIoFormatU8,
  SoundIoFormatU16NE,
  SoundIoFormatU16FE,
  SoundIoFormatU24NE,
  SoundIoFormatU24FE,
  SoundIoFormatU32NE,
  SoundIoFormatU32FE,
};

const std::unordered_set<SoundIoFormat>
  AudioInterfaceSpecSoundIo::foreign_endian_formats =
{
  SoundIoFormatS16FE,
  SoundIoFormatU16FE,
  SoundIoFormatS24FE,
  SoundIoFormatU24FE,
  SoundIoFormatS32FE,
  SoundIoFormatU32FE,
  SoundIoFormatFloat32FE,
  SoundIoFormatFloat64FE,
};


AudioInterfaceSpecSoundIo::AudioInterfaceSpecSoundIo(
  const resonance_core::AudioInterfaceSpec& spec,
  bool unsigned_int,
  bool foreign_endian
): m_format(
    core_type_to_soundio_format(spec.m_data_type, unsigned_int, foreign_endian)
  ),
  m_layout(core_layout_to_soundio_layout(spec.m_layout)),
  m_sample_rate(core_sample_rate_to_soundio_sample_rate(spec.m_sample_rate)) {}


AudioInterfaceSpecSoundIo::AudioInterfaceSpecSoundIo(
  const resonance_core::AudioInterfaceSpec& spec
): AudioInterfaceSpecSoundIo(spec, false, false) {}


int
  AudioInterfaceSpecSoundIo::core_sample_rate_to_soundio_sample_rate(
    unsigned int sample_rate
  )
{
  if (sample_rate > static_cast<unsigned int>(std::numeric_limits<int>::max()))
  {
    throw InvalidSpecValuesException(
      "Sample rate of " + std::to_string(sample_rate) + " cannot exceed max value for "
      + "signed int (" + std::to_string(std::numeric_limits<int>::max()) + ")"
    );
  }

  return static_cast<int>(sample_rate);
}


SoundIoFormat
  AudioInterfaceSpecSoundIo::core_type_to_soundio_format(
    resonance_core::AudioDataType type,
    bool unsigned_int,
    bool foreign_endian
  )
{
  // 0bFU
  // F - foreign endian, U - unsigned int
  int format_index =
    (static_cast<int>(foreign_endian) << 1) | static_cast<int>(unsigned_int);

  const std::array<SoundIoFormat, 4>& possible_formats = formats.at(type);

  return possible_formats.at(format_index);
}


SoundIoChannelLayout
  AudioInterfaceSpecSoundIo::core_layout_to_soundio_layout(
    const resonance_core::AudioChannelLayout& layout
  )
{
  if (layout.m_channel_ids.size() > SOUNDIO_MAX_CHANNELS)
  {
    throw InvalidSpecValuesException(
      "SoundIo only supports up to " + std::to_string(SOUNDIO_MAX_CHANNELS)
      + " channels"
    );
  }

  SoundIoChannelLayout layout_soundio;
  
  layout_soundio.channel_count = layout.m_channel_ids.size();

  for (
    int channel_index = 0;
    channel_index < layout.m_channel_ids.size();
    channel_index++
  ) {
    layout_soundio.channels[channel_index] = channel_ids.at(
      layout.m_channel_ids.at(channel_index)
    );
  }

  return layout_soundio;
}


const std::array<SoundIoFormat, 4>&
  AudioInterfaceSpecSoundIo::get_compatable_formats(resonance_core::AudioDataType type)
{
  return formats.at(type);
}

bool
  AudioInterfaceSpecSoundIo::is_unsigned(SoundIoFormat format)
{
  return unsigned_formats.contains(format);
}

bool
  AudioInterfaceSpecSoundIo::is_foreign_endian(SoundIoFormat format)
{
  return foreign_endian_formats.contains(format);
}
