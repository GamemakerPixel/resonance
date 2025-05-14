#include "core/audio_output_device_soundio.h"

#include <cstdint>
#include <memory>

using namespace resonance_core;


AudioOutputDeviceSoundIo::AudioOutputDeviceSoundIo(
  const SoundIo& context,
  int device_index
) : m_device(soundio_get_output_device(&context, device_index), &soundio_device_unref)
{
  if (!m_device)
  {
    //Error
  }

  if (m_device->probe_error != SoundIoErrorNone)
  {
    //Error
  }
}


std::unique_ptr<AudioOutputStream>
  AudioOutputDeviceSoundIo::get_stream()
{

}


std::size_t
  AudioOutputDeviceSoundIo::get_backend_relative_hash()
{
  std::size_t id_hash = std::hash<std::string>(m_device->id);
  std::size_t 
}
