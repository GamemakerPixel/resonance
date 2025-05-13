#include "core/backend_loader.h"

#include <memory>
#include <string>
#include <unordered_map>

#include "core/audio_backend.h"
#include "core/backend_factory.h"

using namespace resonance_core;


BackendLoader::BackendLoader(std::shared_ptr<const BackendFactory> factory)
  : m_factory(factory) {}


std::shared_ptr<AudioBackend> 
  BackendLoader::load_backend(const std::string& backend)
{
  if (m_backends.contains(backend))
  {
    if (std::shared_ptr<AudioBackend> reused_backend = m_backends.at(backend).lock())
    {
      return reused_backend;
    }
  }

  std::shared_ptr<AudioBackend> new_backend = m_factory->construct_backend(backend);

  // Assigned to std::weak_ptr
  m_backends.insert_or_assign(backend, new_backend);

  return new_backend;
}
