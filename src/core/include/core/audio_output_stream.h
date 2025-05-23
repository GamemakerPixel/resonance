#pragma once

#include <stdexcept>
#include <string>

#include "core/abstract_depender.h"


namespace resonance_core
{

class AudioOutputStream: public AbstractDepender
{
public:
  virtual
    ~AudioOutputStream() = default;
};


class OutputStreamConstructionException: public std::runtime_error
{
public:
  OutputStreamConstructionException(const std::string& message)
    : std::runtime_error(message) {}
};


class OutputStreamIncompatableSpecException: public OutputStreamConstructionException
{
public:
  OutputStreamIncompatableSpecException(const std::string& message)
    : OutputStreamConstructionException(message) {}
};

}
