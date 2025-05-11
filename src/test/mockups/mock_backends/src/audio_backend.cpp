#include "mock_backends/audio_backend.h"

#include <string>
#include <vector>

using namespace mock_backends;


AudioBackend::AudioBackend(int id)
  : m_id(id) {}


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
