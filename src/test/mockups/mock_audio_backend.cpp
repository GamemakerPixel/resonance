#include "mock_audio_backend.h"


MockBackend::MockBackend(std::unordered_set<std::string> avaliable_backends) :
  m_avaliable_backends(avaliable_backends) {}


std::unordered_set<std::string> MockBackend::get_avaliable_backends() const
{
  return m_avaliable_backends;
}


void MockBackend::connect_to_backend(const std::string& backend_name)
{
  if (m_connect_enabled)
  {
    
  }
}


std::string MockBackend::get_connected_backend_name() const
{

}
