#include "mock_backends/audio_output_device.h"

#include <memory>
#include <utility>

#include "core/audio_output_device.h"

#include "mock_backends/audio_backend.h"

using namespace mock_backends;


AudioOutputDevice::AudioOutputDevice(
  std::pair<int, int> id
) : m_id(id) {}


std::pair<int, int>
  AudioOutputDevice::get_id() const
{
  return m_id;
}
