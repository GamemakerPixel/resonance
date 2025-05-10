#pragma once

#include <memory>
#include <string>
#include <vector>

#include <soundio/soundio.h>

#include "core/audio_backend.h"


namespace resonance_core {
  class AudioBackendSoundIo: public AudioBackend {
  private:
    const std::unique_ptr<SoundIo, void(*)(SoundIo*)> m_context;

  public:
    AudioBackendSoundIo(SoundIoBackend backend);

    std::vector<std::string>
      get_output_device_names() const override;

    /*
    std::shared_ptr<OutputDevice>
      get_output_device(int device_index) const override;

    std::shared_ptr<OutputDevice>
      get_default_output_device() const override;
    */
  };
}
