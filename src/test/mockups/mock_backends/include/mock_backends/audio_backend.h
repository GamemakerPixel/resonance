#pragma once

#include <string>
#include <vector>

#include "core/audio_backend.h"


namespace mock_backends
{

class AudioBackend: public resonance_core::AudioBackend
{
private:
  const int m_id;

public:
  AudioBackend(int id);

  std::vector<std::string>
    get_output_device_names() const override;

  int get_id() const;
};

}
