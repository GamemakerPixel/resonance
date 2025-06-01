#include "core/backend_manager.h"

#include <memory>
#include <string>
#include <unordered_set>

#include "core/audio_backend.h"
#include "core/audio_output_device.h"
#include "core/audio_output_stream.h"
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

bool
	BackendManager::is_spec_compatable_with_output_device(
		const std::string& backend,
		const std::string& device,
		const AudioInterfaceSpec& spec)
{
	std::shared_ptr<AudioOutputDevice> loaded_device =
		m_loader->load_output_device(backend, device);

	return loaded_device->is_spec_compatable(spec);
}


std::unique_ptr<AudioOutputStream>
  BackendManager::get_stream(
    const std::string& backend,
    const std::string& device,
    const AudioInterfaceSpec& spec)
{
  return m_loader->create_output_stream(backend, device, spec);
}

