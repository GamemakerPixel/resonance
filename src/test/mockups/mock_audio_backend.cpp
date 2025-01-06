#include "mock_audio_backend.h"


MockAudioBackend::MockAudioBackend(
  const std::unordered_set<std::string>& avaliable_backends
) : m_avaliable_backends(avaliable_backends) {}


std::unordered_set<std::string> MockAudioBackend::get_avaliable_backends() const
{
  return m_avaliable_backends;
}


void MockAudioBackend::connect_to_backend(const std::string& backend_name)
{
  if (!m_avaliable_backends.contains(backend_name))
  {
    throw BackendExceptions::unavaliable_backend(backend_name);
  }

  m_current_backend = backend_name;
}


std::string MockAudioBackend::get_connected_backend_name() const
{
  return m_current_backend;
}
