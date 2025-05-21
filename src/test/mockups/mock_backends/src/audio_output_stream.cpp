#include "mock_backends/audio_output_stream.h"

#include <utility>

#include "core/audio_interface_spec.h"
#include "core/audio_output_stream.h"

using namespace mock_backends;


AudioOutputStream::AudioOutputStream(
  resonance_core::AudioInterfaceSpec spec,
  std::pair<int, int> device_id
)
  : resonance_core::AudioOutputStream(spec), m_device_id(device_id) {}


std::pair<int, int>
  AudioOutputStream::get_device_id()
{
  return m_device_id;
}
