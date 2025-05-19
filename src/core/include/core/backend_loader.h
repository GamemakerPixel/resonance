#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "core/abstract_subscription_ptr.h"


namespace resonance_core
{

class AudioBackend;
class AudioOutputDevice;
class BackendFactory;

class BackendLoader
{
private:
  const std::shared_ptr<const BackendFactory> m_factory;

  std::unordered_map<std::string, AbstractSubscriptionPtr<AudioBackend>> m_backends;
  std::unordered_map<
    std::string, std::unordered_map<
      std::string,
      AbstractSubscriptionPtr<AudioOutputDevice>
    >
  > m_output_devices;

public:
  BackendLoader(std::shared_ptr<const BackendFactory> factory);

  std::shared_ptr<AudioBackend>
    load_backend(const std::string& backend);

  std::shared_ptr<AudioOutputDevice>
    load_output_device(const std::string& backend, const std::string& device);
};

}
