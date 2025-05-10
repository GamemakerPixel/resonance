#include "core/audio_backend_soundio.h"

#include <memory>
#include <string>
#include <vector>

#include <soundio/soundio.h>


using namespace resonance_core;


AudioBackendSoundIo::AudioBackendSoundIo(SoundIoBackend backend)
  : m_context(soundio_create(), &soundio_destroy)
{
  const int connect_error = soundio_connect_backend(m_context.get(), backend);

  if (connect_error != SoundIoErrorNone)
  {
    throw AudioBackendConnectionException(soundio_strerror(connect_error));
  }

  soundio_flush_events(m_context.get());
}


std::vector<std::string>
  AudioBackendSoundIo::get_output_device_names() const
{
  soundio_flush_events(m_context.get());

  const int device_count = soundio_output_device_count(m_context.get());

  std::vector<std::string> device_names;
  device_names.reserve(device_count);

  for (int device_index = 0; device_index < device_count; device_index++) {
    std::unique_ptr<SoundIoDevice, void(*)(SoundIoDevice*)>
    device(
      soundio_get_output_device(m_context.get(), device_index),
      &soundio_device_unref
    );

    device_names.push_back(device->name);
  }

  return device_names;
}

/*
std::shared_ptr<OutputDevice>
  AudioBackendSoundIo::get_output_device(int device_index) const
{

}


std::shared_ptr<OutputDevice>
  AudioBackendSoundIo::get_default_output_device() const
{

}
*/
