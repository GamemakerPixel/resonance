#include "mock_backends/audio_output_device.h"

#include <memory>
#include <utility>

#include "core/audio_output_device.h"

#include "mock_backends/audio_backend.h"

using namespace mock_backends;


int AudioOutputDevice::instance_count = 0;


AudioOutputDevice::AudioOutputDevice(
  std::pair<int, int> id
) : m_id(id), m_unique_instance_id(instance_count)
{
  instance_count++;
}


std::pair<int, int>
  AudioOutputDevice::get_id() const
{
  return m_id;
}


int
  AudioOutputDevice::get_unique_instance_id() const
{
  return m_unique_instance_id;
}
