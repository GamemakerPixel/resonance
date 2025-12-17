#pragma once

#include <functional>
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

	//virtual void
	//	start(std::function<void(int)> write_callback) = 0;
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
