#include <iostream>
#include <string>
#include <unordered_set>

#include "core/backend_factory.h"
#include "core/backend_manager.h"
#include "soundio_backends/soundio_backends.h"


int
  main()
{
  std::cout << "Welcome to Resonance!\n";

  auto factory = std::make_unique<resonance_core::BackendFactory>();

  soundio_backends::register_backends(*factory);

  auto manager = std::make_unique<resonance_core::BackendManager>(std::move(factory));

  std::unordered_set<std::string> backend_names = manager->get_backend_names();

  std::cout << "Avaliable Backends:\n";
  for (const std::string& name: backend_names)
  {
    std::cout << "\t" << name << "\n";
  }
  std::cout << std::endl;

  for (const std::string& name: backend_names)
  {
    std::unordered_set<std::string> device_names =
      manager->get_output_device_names(name);

    std::cout << "Avaliable output devices for " << name << " include:\n";
    for (const std::string& device: device_names)
    {
      std::cout << "\t" << device << "\n";
    }
    std::cout << std::endl;
  }
}
