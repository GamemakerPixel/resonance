#pragma once

#include <vector>


namespace resonance_core
{

// https://en.wikipedia.org/wiki/Surround_sound#Standard_speaker_channels
// With some modification and borrowing from SoundIo
enum class AudioChannelId
{
  LEFT,
  RIGHT,
  CENTER,
  LFE,
  BACK_LEFT,
  BACK_RIGHT,
  FRONT_LEFT_CENTER,
  FRONT_RIGHT_CENTER,
  BACK_CENTER,
  SIDE_LEFT,
  SIDE_RIGHT,
  TOP_CENTER,
  TOP_FRONT_LEFT,
  TOP_FRONT_CENTER,
  TOP_FRONT_RIGHT,
  TOP_BACK_LEFT,
  TOP_BACK_CENTER,
  TOP_BACK_RIGHT,
  AUX,
};


struct AudioChannelLayout
{
  std::vector<AudioChannelId> m_channel_ids;

  AudioChannelLayout(std::vector<AudioChannelId> channel_ids);

  bool
    operator==(const AudioChannelLayout& other) const;
  
  bool
    operator!=(const AudioChannelLayout& other) const;
};

namespace standard_layouts
{
  extern const AudioChannelLayout mono;
  extern const AudioChannelLayout stereo;
}

}
