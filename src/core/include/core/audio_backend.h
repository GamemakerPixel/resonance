#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>


namespace resonance_core {

class AudioBackend {
public:
  virtual
    ~AudioBackend() = default;

  virtual std::vector<std::string>
    get_output_device_names() const = 0;

  /*
  virtual std::shared_ptr<OutputDevice>
    get_output_device(int device_index) const = 0;

  virtual std::shared_ptr<OutputDevice>
    get_default_output_device() const = 0;
  */
};

class AudioBackendConnectionException : public std::runtime_error {
public:
  AudioBackendConnectionException(const std::string& message)
    : std::runtime_error(message) {}
};

}




