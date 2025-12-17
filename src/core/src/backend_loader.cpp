#include "backend_loader.h"

#include <memory>
#include <string>
#include <unordered_map>

#include "abstract_subscription_ptr.h"
#include "audio_backend.h"
#include "audio_output_device.h"
#include "audio_output_stream.h"
#include "backend_factory.h"

using namespace resonance_core;


BackendLoader::BackendLoader(std::shared_ptr<const BackendFactory> factory)
  : m_factory(factory) {}


std::shared_ptr<AudioBackend>
  BackendLoader::load_backend(const std::string& backend)
{
  if (m_backends.contains(backend))
  {
    if (std::shared_ptr<AudioBackend> reused_backend =
      m_backends.at(backend).get_object().lock()
    ) {
      return reused_backend;
    }
  }

  std::shared_ptr<AudioBackend> new_backend = m_factory->construct_backend(backend);

  if (m_backends.contains(backend))
  {
    m_backends.erase(backend);
  }

  m_backends.emplace(
    backend,
    AbstractSubscriptionPtr<AudioBackend>(new_backend)
  );

  return new_backend;
}


std::shared_ptr<AudioOutputDevice>
  BackendLoader::load_output_device(
    const std::string& backend,
    const std::string& device
  )
{
  if (
    m_output_devices.contains(backend)
    && m_output_devices.at(backend).contains(device))
  {
    if (std::shared_ptr<AudioOutputDevice> reused_device =
      m_output_devices.at(backend).at(device).get_object().lock()
    ) {
      return reused_device;
    }
  }

  std::shared_ptr<AudioBackend> loaded_backend = load_backend(backend);


  if (!m_output_devices.contains(backend))
  {
    m_output_devices.emplace(
      backend,
      std::unordered_map<std::string, AbstractSubscriptionPtr<AudioOutputDevice>>()
    );
  }
  else if (m_output_devices.at(backend).contains(device))
  {
    m_output_devices.at(backend).erase(device);
  }

  std::shared_ptr<AudioOutputDevice> new_device =
    loaded_backend->create_output_device(device);
  m_output_devices.at(backend).emplace(
    device,
    AbstractSubscriptionPtr<AudioOutputDevice>(new_device)
  );

  m_backends.at(backend).subscribe_to_depender(*new_device);

  return new_device;
}


std::unique_ptr<AudioOutputStream>
  BackendLoader::create_output_stream(
    const std::string& backend,
    const std::string& device,
    const AudioInterfaceSpec& spec
  )
{
  std::shared_ptr<AudioOutputDevice> loaded_device = load_output_device(
    backend, device
  );

  std::unique_ptr<AudioOutputStream> stream = loaded_device->create_stream(spec);

  m_output_devices.at(backend).at(device).subscribe_to_depender(*stream);

  return stream;
}
