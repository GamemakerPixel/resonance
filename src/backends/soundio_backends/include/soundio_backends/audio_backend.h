#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_set>

#include <soundio/soundio.h>

#include "core/audio_backend.h"


namespace soundio_backends
{

class AudioBackend: public resonance_core::AudioBackend
{
private:
  const std::unique_ptr<SoundIo, void(*)(SoundIo*)> m_context;

public:
  AudioBackend(SoundIoBackend backend);

  ~AudioBackend();

  std::unordered_set<std::string>
    get_output_device_names() const override;
};

}
