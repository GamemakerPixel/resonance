#include "mock_backends/audio_output_stream.h"

#include <utility>

#include "core/core.h"

using namespace mock_backends;


AudioOutputStream::AudioOutputStream(
  std::pair<int, int> device_id
)
  : m_device_id(device_id) {}


std::pair<int, int>
  AudioOutputStream::get_device_id()
{
  return m_device_id;
}
