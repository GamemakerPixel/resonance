#include <iostream>
#include <vector>

#include "model/output_backend_manager.h"


void discover_availiable_backends(const OutputBackendManager& backend_manager)
{
  std::vector<OutputBackend> avaliable_backends = backend_manager.get_avaliable_backends(); 

  std::cout << "Avaliable backends: " << std::endl;
  for (auto backend : avaliable_backends)
  {
    std::cout << "\t" << backend_manager.get_backend_name(backend) << "\n";
  }
}


int main()
{
  std::cout << "Welcome to Resonance!" << std::endl;

  OutputBackendManager backend_manager;
  
  discover_availiable_backends(backend_manager);

  OutputBackend backend = OutputBackend::ALSA;
  std::cout << "Connecting to " << backend_manager.get_backend_name(backend) << std::endl;

  backend_manager.connect_to_backend(backend);
  std::cout << "Connected to " << backend_manager.get_backend_name(backend) << std::endl;
}

