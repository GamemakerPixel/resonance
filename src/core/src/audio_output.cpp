#include "core/audio_output.h"

#include "core/audio_backend.h"


AudioOutput::AudioOutput(
  AudioBackend& backend,
  const std::vector<std::string>& connection_order
) : m_backend(backend), m_connection_order(connection_order) {}


void AudioOutput::connect_backend()
{
  for (const std::string& backend_name: m_connection_order)
  {
    try
    {
      m_backend.connect_to_backend(backend_name);
      return;
    }
    catch (BackendExceptions::unavaliable_backend& exception)
    {
      continue;
    }
  }

  throw AudioOutputExceptions::no_requested_backends();
}


std::string AudioOutput::get_connected_backend() const
{
  return m_backend.get_connected_backend_name();
}
