#pragma once

#include <stdexcept>
#include <string>

#include "core/abstract_depender.h"
#include "core/audio_interface_spec.h"


namespace resonance_core
{

class AudioOutputStream: public AbstractDepender
{
protected:
  const AudioInterfaceSpec m_spec;
public:
  AudioOutputStream(AudioInterfaceSpec spec);

  virtual
    ~AudioOutputStream() = default;
};


class OutputStreamConstructionException: public std::runtime_error
{
  OutputStreamConstructionException(const std::string& message)
    : std::runtime_error(message) {}
};

}
