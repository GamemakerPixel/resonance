#include "mock_backends/audio_output_device.h"
#include "mock_backends/audio_output_stream.h"

#include <memory>
#include <utility>

using namespace mock_backends;


int AudioOutputDevice::instance_count = 0;


AudioOutputDevice::AudioOutputDevice(
  std::pair<int, int> id
) : m_id(id), m_unique_instance_id(instance_count)
{
  instance_count++;
}


std::unique_ptr<resonance_core::AudioOutputStream>
  AudioOutputDevice::create_stream(resonance_core::AudioInterfaceSpec spec) const
{
  return std::make_unique<AudioOutputStream>(spec, m_id);
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
