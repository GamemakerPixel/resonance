#include "core/audio_output_device.h"

#include <memory>

using namespace resonance_core;


namespace resonance_core
{

class AudioBackend;

}


AudioOutputDevice::AudioOutputDevice(std::shared_ptr<AudioBackend> backend)
  : m_backend(backend) {}
