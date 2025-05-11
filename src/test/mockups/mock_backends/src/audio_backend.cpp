#include "mock_backends/audio_backend.h"

#include <string>
#include <vector>

using namespace mock_backends;


AudioBackend::AudioBackend(int id)
  : m_id(id)
{
  if (id < 0)
  {
    throw std::runtime_error("ID cannot be less than 0");
  }
}


std::vector<std::string>
  AudioBackend::get_output_device_names() const
{
  std::vector<std::string> names;

  return names;
}


int
  AudioBackend::get_id() const
{
  return m_id;
}
