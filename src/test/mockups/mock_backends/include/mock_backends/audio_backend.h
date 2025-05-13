#pragma once

#include <string>
#include <unordered_set>

#include "core/audio_backend.h"


namespace mock_backends
{

class AudioBackend: public resonance_core::AudioBackend
{
private:
  static constexpr std::string DEVICE_PREFIX = "Mock Device ";

  static int instance_count;

  const int m_id;
  const int m_device_count;
  const int m_unique_instance_id;

public:
  AudioBackend(int id, int device_count);

  std::unordered_set<std::string>
    get_output_device_names() const override;

  int get_id() const;
  
  int get_unique_instance_id() const;
};

}
