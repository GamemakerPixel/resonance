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
  if (
    !m_avaliable_backends.contains(backend_name)
    || m_backend_statuses.contains(backend_name)
    && m_backend_statuses.at(backend_name) == BackendStatus::UNAVALIABLE)
  {
    throw BackendExceptions::unavaliable_backend(backend_name);
  }

  m_current_backend = backend_name;
}


std::string MockAudioBackend::get_connected_backend_name() const
{
  return m_current_backend;
}


void MockAudioBackend::set_backend_status(
  const std::string& backend_name,
  BackendStatus status)
{
  if (status == BackendStatus::AVALIABLE)
  {
    if (m_backend_statuses.contains(backend_name))
    {
      m_backend_statuses.erase(backend_name);
    }
    return;
  }

  m_backend_statuses.insert({backend_name, status});
}
