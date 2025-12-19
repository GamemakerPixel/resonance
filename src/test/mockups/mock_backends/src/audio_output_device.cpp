#include "audio_output_device.h"
#include "audio_output_stream.h"

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
  AudioOutputDevice::create_stream(
    const resonance_core::AudioInterfaceSpec& /*spec*/
  ) const
{
  return std::make_unique<AudioOutputStream>(m_id);
}

bool
	AudioOutputDevice::is_spec_compatable(
		const resonance_core::AudioInterfaceSpec& spec
	) const
{
	return false;
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
