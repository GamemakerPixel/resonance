#include <iostream>
#include <unordered_set>
#include <string>

#include "core/soundio_audio_backend.h"


void discover_availiable_backends(const SoundioAudioBackend& backend)
{
  std::unordered_set<std::string> avaliable_backends = backend.get_avaliable_backends(); 

  std::cout << "Avaliable backends: \n";
  for (const std::string& avaliable_backend: avaliable_backends)
  {
    std::cout << "\t" << avaliable_backend << "\n";
  }
}


int main()
{
  std::cout << "Welcome to Resonance!\n";

  SoundioAudioBackend backend;
  
  discover_availiable_backends(backend);
/*
  std::cout << "Connecting to best avaliable backend.\n";

  backend_manager.connect_to_first_avaliable_backend();

  const OutputBackend backend = backend_manager.get_connected_backend();
  std::cout << "Connected to " << backend_manager.get_backend_name(backend) << std::endl;
*/
}
