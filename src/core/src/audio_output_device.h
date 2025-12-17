#pragma once

#include <memory>
#include <stdexcept>
#include <string>

#include "abstract_depender.h"
#include "audio_interface_spec.h"


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

  virtual bool
    is_spec_compatable(const AudioInterfaceSpec& spec) const = 0;
};


class OutputDeviceConnectionException: public std::runtime_error
{
public:
  OutputDeviceConnectionException(const std::string& message)
    : std::runtime_error(message) {}
};


class IncompatableSpecException: public std::logic_error
{
public:
  IncompatableSpecException(const std::string& message)
    : std::logic_error(message) {}
};

}
