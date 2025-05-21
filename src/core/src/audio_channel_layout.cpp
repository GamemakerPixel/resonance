#include "core/audio_channel_layout.h"


using namespace resonance_core;


AudioChannelLayout::AudioChannelLayout(std::vector<AudioChannelId> channel_ids)
  : m_channel_ids(channel_ids) {}


bool
  AudioChannelLayout::operator==(const AudioChannelLayout& other) const
{
  return m_channel_ids == other.m_channel_ids;
}


bool
  AudioChannelLayout::operator!=(const AudioChannelLayout& other) const
{
  return m_channel_ids != other.m_channel_ids;
}


const AudioChannelLayout standard_layouts::mono({
  AudioChannelId::CENTER
});

const AudioChannelLayout standard_layouts::stereo({
  AudioChannelId::LEFT,
  AudioChannelId::RIGHT
});
