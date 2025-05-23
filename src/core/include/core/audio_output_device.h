#pragma once

#include <memory>
#include <stdexcept>
#include <string>

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
    create_stream(const AudioInterfaceSpec& spec) const = 0;
};


class OutputDeviceConnectionException: public std::runtime_error
{
public:
  OutputDeviceConnectionException(const std::string& message)
    : std::runtime_error(message) {}
};

}
