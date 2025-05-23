#include "soundio_backends/audio_output_device.h"

#include <memory>

#include <soundio/soundio.h>

#include "core/audio_output_device.h"

#include "soundio_backends/audio_output_stream.h"

using namespace soundio_backends;


AudioOutputDevice::AudioOutputDevice(
  std::unique_ptr<SoundIoDevice, void(*)(SoundIoDevice*)> device
) : m_device(std::move(device))
{
  if (m_device->probe_error != SoundIoErrorNone)
  {
    throw resonance_core::OutputDeviceConnectionException(
      soundio_strerror(m_device->probe_error)
    );
  }
}


std::unique_ptr<resonance_core::AudioOutputStream>
  AudioOutputDevice::create_stream(
    const resonance_core::AudioInterfaceSpec& spec
  ) const
{
  // TODO: Validate spec works for device.

  std::unique_ptr<SoundIoOutStream, void(*)(SoundIoOutStream*)> stream(
    soundio_outstream_create(m_device.get()),
    &soundio_outstream_destroy
  );

  return std::make_unique<AudioOutputStream>(std::move(stream), spec);
}
