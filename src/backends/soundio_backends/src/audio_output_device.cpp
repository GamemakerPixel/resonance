#include "soundio_backends/audio_output_device.h"

#include <limits>
#include <memory>

#include <soundio/soundio.h>
#include <string>
#include <unordered_set>

#include "core/audio_output_device.h"

#include "soundio_backends/audio_interface_spec_soundio.h"
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
	validate_spec(spec);

  std::unique_ptr<SoundIoOutStream, void(*)(SoundIoOutStream*)> stream(
    soundio_outstream_create(m_device.get()),
    &soundio_outstream_destroy
  );

  return std::make_unique<AudioOutputStream>(std::move(stream), spec);
}


bool
  AudioOutputDevice::is_spec_compatable(
    const resonance_core::AudioInterfaceSpec& spec
  ) const
{
  try
  {
		validate_spec(spec);
  }
  catch (const InvalidSpecValuesException&)
  {
    return false; 
  }
	catch (const resonance_core::IncompatableSpecException&)
	{
		return false;
	}

	return true;
}


void
  AudioOutputDevice::validate_spec(const resonance_core::AudioInterfaceSpec& spec) const
{
  AudioInterfaceSpecSoundIo soundio_spec(spec);

  if (!soundio_device_supports_sample_rate(m_device.get(), soundio_spec.m_sample_rate))
  {
    throw resonance_core::IncompatableSpecException(
      "Sample rate" + std::to_string(spec.m_sample_rate)
      + " is not compatable with this device"
    );
  }

  if (negotiate_compatable_format(spec.m_data_type) == SoundIoFormatInvalid)
  {
    throw resonance_core::IncompatableSpecException(
      "Device is not compatable with format: "
      + audio_data_type_to_string(spec.m_data_type)
    );
  }

  if (!soundio_device_supports_layout(m_device.get(), &soundio_spec.m_layout))
  {
    throw resonance_core::IncompatableSpecException(
			"Device does not support channel layout: " + spec.m_layout.to_string()
    );
  }
}


SoundIoFormat
  AudioOutputDevice::negotiate_compatable_format(
    resonance_core::AudioDataType type
  ) const
{
  std::unordered_set<SoundIoFormat> supported_formats;

  for (int format_index = 0; format_index < m_device->format_count; format_index++)
  {
    supported_formats.insert(m_device->formats[format_index]);
  }

  SoundIoFormat best_format = SoundIoFormatInvalid;
  int format_cost = std::numeric_limits<int>::max();

  for (SoundIoFormat format: AudioInterfaceSpecSoundIo::get_compatable_formats(type))
  {
    if (supported_formats.contains(format))
    {
      int cost = 0;

      if (AudioInterfaceSpecSoundIo::is_unsigned(format))
      {
        cost += 2;
      }
      if (AudioInterfaceSpecSoundIo::is_foreign_endian(format))
      {
        cost += 1;
      }

      if (cost < format_cost)
      {
        best_format = format;
        format_cost = cost;
      }
    }
  }

  return best_format;
}
