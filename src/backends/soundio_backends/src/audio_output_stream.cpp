#include "audio_output_stream.h"
#include "core/core.h"

#include <soundio/soundio.h>

using namespace soundio_backends;


AudioOutputStream::AudioOutputStream(
  std::unique_ptr<SoundIoOutStream, void(*)(SoundIoOutStream*)> stream,
  const AudioInterfaceSpecSoundIo& spec
): m_stream(std::move(stream))
{
	if (!m_stream)
	{
		return;
	}

	m_stream->sample_rate = spec.m_sample_rate;
	m_stream->format = spec.m_format;
	m_stream->layout = spec.m_layout;

	int error = soundio_outstream_open(m_stream.get());

	if (error == SoundIoErrorIncompatibleDevice)
	{
		throw resonance_core::IncompatableSpecException(
			"Spec is incompatable with this device"
		);
	}

	if (error != SoundIoErrorNone)
	{
		throw resonance_core::OutputStreamConstructionException(soundio_strerror(error));
	}
}
