#include "register_backends.h"

#include <array>
#include <memory>
#include <string>

#include <soundio/soundio.h>

#include "core/core.h"

#include "audio_backend.h"

using namespace soundio_backends;


void soundio_backends::register_backends(resonance_core::BackendFactory& factory)
{
  constexpr std::array<SoundIoBackend, 5> possible_backends = {
    SoundIoBackendJack,
    SoundIoBackendPulseAudio,
    SoundIoBackendAlsa,
    SoundIoBackendCoreAudio,
    SoundIoBackendWasapi,
  };

  for (SoundIoBackend backend: possible_backends)
  {
    if (!soundio_have_backend(backend))
    {
      continue;
    }

    const std::string name = soundio_backend_name(backend);

    factory.register_backend(name, [backend]()
    {
      return std::make_unique<AudioBackend>(backend);
    });
  }
}
