#pragma once

#include <cstdint>
#include <memory>


namespace resonance_core
{

class AudioOutputDevice
{
public:
  virtual
    ~AudioOutputDevice() = default;

  virtual std::unique_ptr<AudioOutputStream>
    get_stream() = 0;
  
  virtual std::size_t
    get_backend_relative_hash() = 0;
};

}
