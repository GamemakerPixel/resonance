#include "mock_backends/audio_backend.h"

#include <string>
#include <unordered_set>

using namespace mock_backends;


int AudioBackend::instance_count = 0;


AudioBackend::AudioBackend(int id, int device_count)
  : m_id(id), m_device_count(device_count), m_unique_instance_id(instance_count)
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

  for (int device_index = 0; device_index < m_device_count; device_index++)
  {
    names.emplace(
      DEVICE_PREFIX + std::to_string(m_id) + "-" + std::to_string(device_index)
    );
  }

  return names;
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
