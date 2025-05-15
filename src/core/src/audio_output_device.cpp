#include "core/audio_output_device.h"

#include <memory>

using namespace resonance_core;


namespace resonance_core
{

class AudioBackend;

}


AudioOutputDevice::AudioOutputDevice(std::shared_ptr<AudioBackend> backend)
  : m_backend(backend)
{
  if (!backend)
  {
    throw NullBackendException(
      "Subclasses of AudioOutputDevice must pass a non-null reference to the "
      "AudioBackend it depends on.\nEven if it isn't used in the implementation, this "
      "is nessesary to keep the connection to the backend open while the device is in "
      "use."
    );
  }
}
