#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "abstract_subscription_ptr.h"
#include "audio_data_type.h"
#include "audio_interface_spec.h"


namespace resonance_core
{

class AudioBackend;
class AudioChannelLayout;
class AudioOutputDevice;
class AudioOutputStream;
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

  // data_type, layout, and sample_rate should be passed after negotiation, this should
  // fail if the device doesn't support these exact parameters.
  std::unique_ptr<AudioOutputStream>
    create_output_stream(
      const std::string& backend,
      const std::string& device,
      const AudioInterfaceSpec& spec
    );
};

}
