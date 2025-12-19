#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "core/core.h"


namespace resonance_core
{

class AudioOutputDevice;

}


namespace mock_backends
{

class AudioBackend: public resonance_core::AudioBackend
{
private:
  static constexpr std::string DEVICE_PREFIX = "Mock Device ";

  static int instance_count;

  const int m_id;
  const int m_unique_instance_id;
  const std::unordered_map<std::string, int> m_devices;

public:
  AudioBackend(int id, int device_count);

  std::unordered_set<std::string>
    get_output_device_names() const override;
 
  std::unique_ptr<resonance_core::AudioOutputDevice>
    create_output_device(const std::string& name) const override;

  int
    get_id() const;

  int
    get_unique_instance_id() const;

private:
  static std::unordered_map<std::string, int>
    generate_devices(int device_count, int id);
};

}
