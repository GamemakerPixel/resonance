#include "output_backend_manager.h"

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include <soundio/soundio.h>

//OutputBackend();
//~OutputBackend();
//std::vector<OutputBackend> get_avaliable_backends();
//void connect_to_first_avaliable_backend();
//void connect_to_backend(OutputBackend backend);
//OutputBackend get_connected_backend();
//std::string get_backend_name(OutputBackend backend);

const std::unordered_map<SoundIoBackend, OutputBackend> OutputBackendManager::soundio_backend_conversion_map =
{
  {SoundIoBackendNone, OutputBackend::NONE},
  {SoundIoBackendJack, OutputBackend::JACK},
  {SoundIoBackendPulseAudio, OutputBackend::PULSE_AUDIO},
  {SoundIoBackendAlsa, OutputBackend::ALSA},
  {SoundIoBackendCoreAudio, OutputBackend::CORE_AUDIO},
  {SoundIoBackendWasapi, OutputBackend::WASAPI},
  {SoundIoBackendDummy, OutputBackend::DUMMY},
};

const std::unordered_map<OutputBackend, SoundIoBackend> OutputBackendManager::reversed_backend_conversion_map =
{
  {OutputBackend::NONE, SoundIoBackendNone},
  {OutputBackend::JACK, SoundIoBackendJack},
  {OutputBackend::PULSE_AUDIO, SoundIoBackendPulseAudio},
  {OutputBackend::ALSA, SoundIoBackendAlsa},
  {OutputBackend::CORE_AUDIO, SoundIoBackendCoreAudio},
  {OutputBackend::WASAPI, SoundIoBackendWasapi},
  {OutputBackend::DUMMY, SoundIoBackendDummy},
};

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


OutputBackendManager::OutputBackendManager()
{
  backend_context = soundio_create();
  connected_backend = OutputBackend::NONE;
}


OutputBackendManager::~OutputBackendManager()
{
  soundio_destroy(backend_context);
}


std::vector<OutputBackend> OutputBackendManager::get_avaliable_backends() const
{
  int avaliable_backends_count = soundio_backend_count(backend_context);

  std::vector<OutputBackend> avaliable_backends;
  for (int backend_index = 0; backend_index < avaliable_backends_count; backend_index++)
  {
    SoundIoBackend soundio_backend = soundio_get_backend(backend_context, backend_index);
    avaliable_backends.push_back(soundio_backend_conversion_map.at(soundio_backend));
  }

  return avaliable_backends;
}


void OutputBackendManager::connect_to_backend(OutputBackend backend)
{
  SoundIoBackend soundio_backend = reversed_backend_conversion_map.at(backend);

  int error = soundio_connect_backend(backend_context, soundio_backend);

  if (error != SoundIoErrorNone)
  {
    throw std::runtime_error("Could not connect to backend " + get_backend_name(backend));
  }

  connected_backend = backend;
}


std::string OutputBackendManager::get_backend_name(OutputBackend backend) const
{
  return backend_names.at(backend);
}

