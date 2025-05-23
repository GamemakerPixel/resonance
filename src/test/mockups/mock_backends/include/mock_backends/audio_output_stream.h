#pragma once

#include <utility>

#include "core/audio_output_stream.h"


namespace mock_backends
{

class AudioOutputStream: public resonance_core::AudioOutputStream
{
private:
  const std::pair<int, int> m_device_id;

public:
  AudioOutputStream(
    std::pair<int, int> device_id
  );

  std::pair<int, int>  
    get_device_id();
};

}

