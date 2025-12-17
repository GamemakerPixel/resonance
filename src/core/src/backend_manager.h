#pragma once

#include <memory>
#include <string>
#include <unordered_set>

#include "audio_interface_spec.h"
#include "backend_loader.h"


namespace resonance_core
{

class AudioBackend;
class BackendFactory;
//class BackendLoader;

class BackendManager
{
private:
  const std::shared_ptr<const BackendFactory> m_factory;
  const std::unique_ptr<BackendLoader> m_loader;

public:
  BackendManager(std::unique_ptr<const BackendFactory> factory);

  std::unordered_set<std::string>
    get_backend_names() const;

  std::unordered_set<std::string>
    get_output_device_names(const std::string& backend_name);

	bool
		is_spec_compatable_with_output_device(
			const std::string& backend,
			const std::string& device,
			const AudioInterfaceSpec& spec
		);

  std::unique_ptr<AudioOutputStream>
    get_stream(
      const std::string& backend,
      const std::string& device,
      const AudioInterfaceSpec& spec
    );
};

}
