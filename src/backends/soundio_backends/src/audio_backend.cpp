#include "audio_backend.h"

#include <memory>
#include <string>
#include <unordered_set>

#include <soundio/soundio.h>

#include "core/core.h"

#include "audio_output_device.h"

using namespace soundio_backends;


AudioBackend::AudioBackend(SoundIoBackend backend)
  : m_context(
    std::unique_ptr<SoundIo, void(*)(SoundIo*)>(soundio_create(), &soundio_destroy)
  )
{
  const int error = soundio_connect_backend(m_context.get(), backend);

  if (error != SoundIoErrorNone)
  {
    throw resonance_core::AudioBackendConnectionException(soundio_strerror(error));
  }

  soundio_flush_events(m_context.get());
}


AudioBackend::~AudioBackend()
{
  soundio_disconnect(m_context.get());
}


std::unordered_set<std::string>
  AudioBackend::get_output_device_names() const
{
  soundio_flush_events(m_context.get());

  const int device_count = soundio_output_device_count(m_context.get());
  std::unordered_set<std::string> names(device_count);

  for (int device_index = 0; device_index < device_count; device_index++)
  {
    std::unique_ptr<SoundIoDevice, void(*)(SoundIoDevice*)> device(
      soundio_get_output_device(m_context.get(), device_index),
      &soundio_device_unref
    );

    names.insert(device->name);
  }

  return names;
}


std::unique_ptr<resonance_core::AudioOutputDevice>
  AudioBackend::create_output_device(const std::string& name) const
{
  soundio_flush_events(m_context.get());

  const int device_count = soundio_output_device_count(m_context.get());

  int found_device_index = -1;

  for (int device_index = 0; device_index < device_count; device_index++)
  {
    std::unique_ptr<SoundIoDevice, void(*)(SoundIoDevice*)> device(
      soundio_get_output_device(m_context.get(), device_index),
      &soundio_device_unref
    );

    if (device->name == name)
    {
      found_device_index = device_index;
      break;
    }
  }

  if (found_device_index == -1)
  {
    throw resonance_core::DeviceNotAvaliableException(
      name + " is not an avaliable device"
    );
  }

  std::unique_ptr<SoundIoDevice, void(*)(SoundIoDevice*)> device(
    soundio_get_output_device(m_context.get(), found_device_index),
    &soundio_device_unref
  );

  return std::make_unique<AudioOutputDevice>(std::move(device));
}
