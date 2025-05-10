#include <iostream>
#include <string>
#include <vector>

#include <soundio/soundio.h>

#include "core/audio_backend_soundio.h"


void
  try_backend(SoundIoBackend backend_id)
{
  // Will get this via a factory later.
  const std::string name = soundio_backend_name(backend_id);

  try
  {
    // Will also get this via a factory later.
    const resonance_core::AudioBackendSoundIo backend(backend_id);

    std::cout << "Connected to " << name << " successfully. Listing devices...\n";

    const std::vector<std::string> device_names = backend.get_output_device_names();

    for (const std::string& name: device_names) {
      std::cout << name << "\n";
    }
  }
  catch (const resonance_core::AudioBackendConnectionException& exception)
  {
    std::cout << "Failed to connect to " << name << ":\n";
    std::cout << "\t" << exception.what() << "\n";
  }
}


int
  main()
{
  std::cout << "Welcome to Resonance!\n";

  std::cout << "Checking avaliability of backends:\n";

  try_backend(SoundIoBackendJack);
  try_backend(SoundIoBackendPulseAudio);
  try_backend(SoundIoBackendAlsa);
  try_backend(SoundIoBackendCoreAudio);
  try_backend(SoundIoBackendWasapi);
}
