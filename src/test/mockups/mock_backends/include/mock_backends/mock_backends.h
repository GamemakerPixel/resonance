#pragma once

#include <core/core.h>


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

class AudioOutputDevice: public resonance_core::AudioOutputDevice
{
private:
  static int instance_count;

  const std::pair<int, int> m_id;
  const int m_unique_instance_id;

public:
  AudioOutputDevice(
    std::pair<int, int> id
  );
  
  std::unique_ptr<resonance_core::AudioOutputStream>
    create_stream(const resonance_core::AudioInterfaceSpec& spec) const override;
  
	bool
    is_spec_compatable(const resonance_core::AudioInterfaceSpec& spec) const override;

  std::pair<int, int>
    get_id() const;

  int
    get_unique_instance_id() const;
};

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
