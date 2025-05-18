#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_set>


namespace resonance_core {

class AudioOutputDevice;

class AudioBackend {
public:
  virtual
    ~AudioBackend() = default;

  virtual std::unordered_set<std::string>
    get_output_device_names() const = 0;

  virtual std::unique_ptr<AudioOutputDevice>
    create_output_device(const std::string& name) const = 0;
};

class AudioBackendConnectionException: public std::runtime_error
{
public:
  AudioBackendConnectionException(const std::string& message)
    : std::runtime_error(message) {}
};

class DeviceNotAvaliableException: public std::runtime_error
{
public:
  DeviceNotAvaliableException(const std::string& message)
    : std::runtime_error(message) {}
};

}




