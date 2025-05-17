#pragma once

#include <memory>
#include <stdexcept>

#include "core/abstract_depender.h"


namespace resonance_core
{

class AudioBackend;

class AudioOutputDevice: public AbstractDepender
{
public:
  virtual
    ~AudioOutputDevice() = default;

//  virtual std::unique_ptr<AudioOutputStream>
//    get_stream() = 0;
};

}
