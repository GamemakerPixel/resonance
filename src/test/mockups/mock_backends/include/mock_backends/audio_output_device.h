#pragma once

#include <memory>
#include <utility>

#include "core/audio_output_device.h"


namespace mock_backends
{

class AudioBackend;

class AudioOutputDevice: public resonance_core::AudioOutputDevice
{
private:
  const std::pair<int, int> m_id;

public:
  AudioOutputDevice(
    std::pair<int, int> id
  );

  std::pair<int, int>
    get_id() const;
};

}
