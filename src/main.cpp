#include <iostream>
#include <string>
#include <unordered_set>

#include "core/core.h"
#include "soundio_backends/soundio_backends.h"


void register_backends(resonance_core::BackendFactory& factory)
{
  soundio_backends::register_backends(factory);
}


int
  main()
{
  std::cout << "Welcome to Resonance!\n";

  auto factory = std::make_unique<resonance_core::BackendFactory>();

  register_backends(*factory);

  auto manager = std::make_unique<resonance_core::BackendManager>(std::move(factory));

  resonance_core::AudioInterfaceSpec spec(
    resonance_core::AudioDataType::FLOAT32,
    resonance_core::standard_layouts::stereo,
    44100u
  );

	std::cout << "Checking spec compatability...\n";

	if (
		manager->is_spec_compatable_with_output_device(
			"PulseAudio",
			"Built-in Audio Analog Stereo",
			spec
		))
	{
		std::cout << "Spec is compatable.\n";
	}
	else
	{
		std::cout << "Spec is incompatable.\n";	
	}

  std::unique_ptr<resonance_core::AudioOutputStream> stream =
    manager->get_stream("PulseAudio", "Built-in Audio Analog Stereo", spec);

  std::cout << "Successfully created stream.\n";
}
