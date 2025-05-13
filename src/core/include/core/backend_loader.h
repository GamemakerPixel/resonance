#pragma once

#include <memory>
#include <string>
#include <unordered_map>


namespace resonance_core
{

class AudioBackend;
class BackendFactory;

class BackendLoader
{
private:
  const std::shared_ptr<const BackendFactory> m_factory;

  std::unordered_map<std::string, std::weak_ptr<AudioBackend>> m_backends;
  //std::unordered_map<std::string, std::unordered_map<int, std::weak_ptr<AudioOutputDevice>>
  //  m_output_devices;

public:
  BackendLoader(std::shared_ptr<const BackendFactory> factory);

  std::shared_ptr<AudioBackend>
    load_backend(const std::string& backend);
};

}
