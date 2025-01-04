#include "core/output_backend_manager.h"

#include <stdexcept>
#include <array>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include <soundio/soundio.h>


const std::unordered_map<OutputBackend, std::string> OutputBackendManager::backend_names =
{
  {OutputBackend::NONE, "None"},
  {OutputBackend::JACK, "Jack"},
  {OutputBackend::PULSE_AUDIO, "PulseAudio"},
  {OutputBackend::ALSA, "Alsa"},
  {OutputBackend::CORE_AUDIO, "CoreAudio"},
  {OutputBackend::WASAPI, "Wasapi"},
  {OutputBackend::DUMMY, "Dummy"},
};

const std::array<OutputBackend, 6> OutputBackendManager::backend_default_order =
{
  OutputBackend::ALSA,
  OutputBackend::JACK,
  OutputBackend::PULSE_AUDIO,
  OutputBackend::CORE_AUDIO,
  OutputBackend::WASAPI,
};


OutputBackendManager::OutputBackendManager()
{
  backend_context = soundio_create();
  connected_backend = OutputBackend::NONE;
}


OutputBackendManager::~OutputBackendManager()
{
  soundio_destroy(backend_context);
}


std::unordered_set<std::string> OutputBackendManager::get_avaliable_backends() const
{
  const int avaliable_backends_count = soundio_backend_count(backend_context);

  std::unordered_set<OutputBackend> avaliable_backends;
  for (int backend_index = 0; backend_index < avaliable_backends_count; backend_index++)
  {
    const SoundIoBackend soundio_backend = soundio_get_backend(backend_context, backend_index);
    avaliable_backends.insert(static_cast<OutputBackend>(soundio_backend));
  }

  return avaliable_backends;
}


void OutputBackendManager::connect_to_backend(OutputBackend backend)
{
  const SoundIoBackend soundio_backend = static_cast<SoundIoBackend>(backend);

  const int error = soundio_connect_backend(backend_context, soundio_backend);

  if (error != SoundIoErrorNone)
  {
    throw std::runtime_error("Could not connect to backend " + get_backend_name(backend));
  }

  connected_backend = backend;
}


void OutputBackendManager::connect_to_first_avaliable_backend()
{
  const std::unordered_set<OutputBackend> avaliable_backends = get_avaliable_backends();
  for (OutputBackend backend: backend_default_order)
  {
    if (avaliable_backends.contains(backend))
    {
      connect_to_backend(backend);
      return;
    }
  }
}


OutputBackend OutputBackendManager::get_connected_backend() const
{
  return connected_backend;
}


std::string OutputBackendManager::get_backend_name(OutputBackend backend) const
{
  return backend_names.at(backend);
}
