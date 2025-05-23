#include "soundio_backends/audio_output_stream.h"
#include "core/audio_channel_layout.h"
#include "core/audio_data_type.h"
#include <limits>
#include <soundio/soundio.h>

using namespace soundio_backends;


AudioOutputStream::AudioOutputStream(
  std::unique_ptr<SoundIoOutStream, void(*)(SoundIoOutStream*)> stream,
  const resonance_core::AudioInterfaceSpec& spec
): m_stream(std::move(stream))
{
  if (spec.m_sample_rate > static_cast<unsigned int>(std::numeric_limits<int>::max()))
  {
    // Error case, will cause an overflow
  }

  m_stream->sample_rate = static_cast<int>(spec.m_sample_rate);
  m_stream->format = core_type_to_soundio_format(spec.m_data_type);
  m_stream->layout = core_layout_to_soundio_layout(spec.m_layout);

  int error = soundio_outstream_open(m_stream.get());

  // Yes, this could mean the spec is incompatable with the device, but that error is
  // still grouped under here because it is AudioOutputDevice's responsibility to check.
  if (error != SoundIoErrorNone)
  {
    // General creation error
  }
}


SoundIoFormat
  AudioOutputStream::core_type_to_soundio_format(resonance_core::AudioDataType type)
{
  switch (type)
  {
    case resonance_core::AudioDataType::INT8:
      return SoundIoFormatS8;
    case resonance_core::AudioDataType::INT16:
      return SoundIoFormatS16NE;
    case resonance_core::AudioDataType::INT24:
      return SoundIoFormatS24NE;
    case resonance_core::AudioDataType::INT32:
      return SoundIoFormatS32NE;
    case resonance_core::AudioDataType::FLOAT32:
      return SoundIoFormatFloat32NE;
    case resonance_core::AudioDataType::FLOAT64:
      return SoundIoFormatFloat64NE;
    default:
      return SoundIoFormatFloat32NE;
      // Throw a general creation error, because format isn't supported.
  }
}


SoundIoChannelLayout
  AudioOutputStream::core_layout_to_soundio_layout(
    resonance_core::AudioChannelLayout layout
  )
{
  if (layout.m_channel_ids.size() > SOUNDIO_MAX_CHANNELS)
  {
    // Error case, use a invalid spec error later.
    // This shouldn't occur because AudioOutputDevice should prevent it, so this will be
    // a general creation error.
  }

  SoundIoChannelLayout layout_soundio;
  
  layout_soundio.channel_count = layout.m_channel_ids.size();

  for (
    int channel_index = 0;
    channel_index < layout.m_channel_ids.size();
    channel_index++
  ) {
    layout_soundio.channels[channel_index] = core_channel_id_to_soundio_channel_id(
      layout.m_channel_ids.at(channel_index)
    );
  }

  return layout_soundio;
}

SoundIoChannelId
  AudioOutputStream::core_channel_id_to_soundio_channel_id(
    resonance_core::AudioChannelId id
  )
{
  switch (id)
  {
    case resonance_core::AudioChannelId::LEFT:
      return SoundIoChannelIdFrontCenter;
    case resonance_core::AudioChannelId::RIGHT:
      return SoundIoChannelIdFrontRight;
    case resonance_core::AudioChannelId::CENTER:
      return SoundIoChannelIdFrontCenter;
    case resonance_core::AudioChannelId::LFE:
      return SoundIoChannelIdLfe;
    case resonance_core::AudioChannelId::BACK_LEFT:
      return SoundIoChannelIdBackLeft;
    case resonance_core::AudioChannelId::BACK_RIGHT:
      return SoundIoChannelIdBackRight;
    case resonance_core::AudioChannelId::FRONT_LEFT_CENTER:
      return SoundIoChannelIdFrontLeftCenter;
    case resonance_core::AudioChannelId::FRONT_RIGHT_CENTER:
      return SoundIoChannelIdFrontRightCenter;
    case resonance_core::AudioChannelId::BACK_CENTER:
      return SoundIoChannelIdBackCenter;
    case resonance_core::AudioChannelId::SIDE_LEFT:
      return SoundIoChannelIdSideLeft;
    case resonance_core::AudioChannelId::SIDE_RIGHT:
      return SoundIoChannelIdSideRight;
    case resonance_core::AudioChannelId::TOP_CENTER:
      return SoundIoChannelIdTopCenter;
    case resonance_core::AudioChannelId::TOP_FRONT_LEFT:
      return SoundIoChannelIdTopFrontLeft;
    case resonance_core::AudioChannelId::TOP_FRONT_CENTER:
      return SoundIoChannelIdTopFrontCenter;
    case resonance_core::AudioChannelId::TOP_FRONT_RIGHT:
      return SoundIoChannelIdTopFrontRight;
    case resonance_core::AudioChannelId::TOP_BACK_LEFT:
      return SoundIoChannelIdTopBackLeft;
    case resonance_core::AudioChannelId::TOP_BACK_CENTER:
      return SoundIoChannelIdTopBackCenter;
    case resonance_core::AudioChannelId::TOP_BACK_RIGHT:
      return SoundIoChannelIdTopBackRight;
    case resonance_core::AudioChannelId::AUX:
      return SoundIoChannelIdAux;
    default:
      // Throw general creation error
      return SoundIoChannelIdAux;
  }
}
