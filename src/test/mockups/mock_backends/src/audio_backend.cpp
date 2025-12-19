#include "audio_backend.h"

#include <string>
#include <unordered_set>

#include "core/core.h"

#include "audio_output_device.h"

using namespace mock_backends;


int AudioBackend::instance_count = 0;


AudioBackend::AudioBackend(int id, int device_count)
  : m_id(id),
  m_unique_instance_id(instance_count),
  m_devices(generate_devices(device_count, id))
{
  if (id < 0)
  {
    throw std::runtime_error("ID cannot be less than 0");
  }

  instance_count++;
}


std::unordered_set<std::string>
  AudioBackend::get_output_device_names() const
{
  std::unordered_set<std::string> names;

  for (auto [name, _]: m_devices)
  {
    names.insert(name);
  }

  return names;
}


std::unique_ptr<resonance_core::AudioOutputDevice>
  AudioBackend::create_output_device(const std::string& name) const
{
  if (!m_devices.contains(name))
  {
    throw resonance_core::DeviceNotAvaliableException(name + " is not a valid device");
  }

  auto device = std::make_unique<AudioOutputDevice>(
    std::make_pair(m_id, m_devices.at(name))
  );

  return std::move(device);
}


int
  AudioBackend::get_id() const
{
  return m_id;
}


int
  AudioBackend::get_unique_instance_id() const
{
  return m_unique_instance_id;
}


std::unordered_map<std::string, int>
  AudioBackend::generate_devices(int device_count, int id)
{
  std::unordered_map<std::string, int> devices;

  for (int device_index = 0; device_index < device_count; device_index++)
  {
    devices.emplace(
      DEVICE_PREFIX + std::to_string(id) + "-" + std::to_string(device_index),
      device_index
    );
  }

  return devices;
}
