#include "core/backend_manager.h"

#include <memory>
#include <string>
#include <unordered_set>

#include "core/audio_backend.h"
#include "core/backend_factory.h"
#include "core/backend_loader.h"

using namespace resonance_core;


BackendManager::BackendManager(std::unique_ptr<const BackendFactory> factory)
  : m_factory(std::move(factory)),
  m_loader(std::make_unique<BackendLoader>(m_factory)) {}


std::unordered_set<std::string>
  BackendManager::get_backend_names() const
{
  return m_factory->get_backend_names();
}


std::unordered_set<std::string>
  BackendManager::get_output_device_names(const std::string& backend_name)
{
  std::shared_ptr<AudioBackend> backend = m_loader->load_backend(backend_name);

  return backend->get_output_device_names();
}


/*std::shared_ptr<AudioBackend>
  BackendManager::get_backend(const std::string& backend)
{
  
}*/


/*
class BackendManager
{
private:
  const std::unique_ptr<const BackendFactory> m_factory;

  //std::unordered_map<std::string, std::weak_ptr<AudioBackend>> m_backends;
  //std::unordered_map<std::string, std::unordered_map<int, std::weak_ptr<AudioOutputDevice>>
  //  m_devices;

public:
  BackendManager(std::unique_ptr<const BackendFactory> factory);

  std::unordered_set<std::string>
    get_backend_names() const;

  std::unordered_set<std::string>
    get_device_names(const std::string& backend);

  std::unique_ptr<AudioOutputStream>
    get_stream(const std::string& backend, const std::string& device);

private:
  std::shared_ptr<AudioBackend> get_backend(int backend_id);

  //std::shared_ptr<AudioOutputDevice> get_device(int backend_id, int device_id);
};

*/
