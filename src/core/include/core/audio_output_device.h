#pragma once

#include <memory>


namespace resonance_core
{

class AudioBackend;

class AudioOutputDevice
{
private:
const std::shared_ptr<AudioBackend> m_backend;

public:
  AudioOutputDevice(std::shared_ptr<AudioBackend> backend);

  virtual
    ~AudioOutputDevice() = default;

//  virtual std::unique_ptr<AudioOutputStream>
//    get_stream() = 0;
};

}
