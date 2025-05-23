#include "soundio_backends/audio_output_stream.h"

using namespace soundio_backends;


AudioOutputStream::AudioOutputStream(
  std::unique_ptr<SoundIoOutStream, void(*)(SoundIoOutStream*)> stream,
  const resonance_core::AudioInterfaceSpec& spec
): m_stream(std::move(stream))
{
  // TODO: Fill in the stream struct and open here.
}
