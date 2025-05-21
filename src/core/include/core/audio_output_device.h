#pragma once

#include <memory>

#include "core/abstract_depender.h"
#include "core/audio_interface_spec.h"


namespace resonance_core
{

class AudioBackend;
class AudioOutputStream;

class AudioOutputDevice: public AbstractDepender
{
public:
  virtual
    ~AudioOutputDevice() = default;

  virtual std::unique_ptr<AudioOutputStream>
    create_stream(AudioInterfaceSpec spec) const = 0;
};

}
