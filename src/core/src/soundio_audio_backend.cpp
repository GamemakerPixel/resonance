#include "core/soundio_audio_backend.h"

#include <memory>

#include <soundio/soundio.h>


const std::unordered_map<SoundIoBackend, std::string>
SoundioAudioBackend::BACKEND_IDENTIFIERS = 
{
  {SoundIoBackendNone, "soundio_none"},
  {SoundIoBackendJack, "soundio_jack"},
  {SoundIoBackendPulseAudio, "soundio_pulse_audio"},
  {SoundIoBackendAlsa, "soundio_alsa"},
  {SoundIoBackendCoreAudio, "soundio_core_audio"},
  {SoundIoBackendWasapi, "soundio_wasapi"},
  {SoundIoBackendDummy, "soundio_dummy"},
};


SoundioAudioBackend::SoundioAudioBackend() : m_context(
  soundio_create(), soundio_destroy
),
m_avaliable_backends(query_avaliable_backends(m_context.get())) {}


std::unordered_set<std::string> SoundioAudioBackend::get_avaliable_backends() const
{
  std::unordered_set<std::string> backends;
  for (auto backend: m_avaliable_backends)
  {
    backends.insert(backend.first);
  } // Use copy constructor maybe?

  return backends;
}

void SoundioAudioBackend::connect_to_backend(const std::string& backend_name)
{
  // Needs implementation
}


std::string SoundioAudioBackend::get_connected_backend_name() const
{
  //Needs implementation
  return "Implement me!";
}

std::unordered_map<std::string, SoundIoBackend>
SoundioAudioBackend::query_avaliable_backends(SoundIo* context)
{
  std::unordered_map<std::string, SoundIoBackend> avaliable_backends;

  const int backend_count = soundio_backend_count(context);

  for (int backend_index = 0; backend_index < backend_count; backend_index++)
  {
    SoundIoBackend soundio_backend = soundio_get_backend(
      context, backend_index
    );

    std::string backend = BACKEND_IDENTIFIERS.at(soundio_backend);
    avaliable_backends.insert({backend, soundio_backend});
  }

  return avaliable_backends;
}
