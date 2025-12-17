#pragma once

#include <stdexcept>

namespace resonance_core
{

class AudioBackendConnectionException: public std::runtime_error
{
public:
  AudioBackendConnectionException(const std::string& message)
    : std::runtime_error(message) {}
};

class BackendConstructionException: public std::runtime_error
{
public:
  BackendConstructionException(const std::string& message)
    : std::runtime_error(message) {}
};

class DependeeExpiredException: public std::runtime_error
{
public:
  DependeeExpiredException(const std::string& message)
  : std::runtime_error(message) {}
};

class DeviceNotAvaliableException: public std::runtime_error
{
public:
  DeviceNotAvaliableException(const std::string& message)
    : std::runtime_error(message) {}
};

class DuplicateBackendException: public std::logic_error
{
public:
  DuplicateBackendException(const std::string& message)
    : std::logic_error(message) {}
};

class IncompatableSpecException: public std::logic_error
{
public:
  IncompatableSpecException(const std::string& message)
    : std::logic_error(message) {}
};

class InvalidBackendNameException: public std::logic_error
{
public:
  InvalidBackendNameException(const std::string& message)
    : std::logic_error(message) {}
};

class NullDependeeException: public std::logic_error
{
public:
  NullDependeeException(const std::string& message)
  : std::logic_error(message) {}
};

class OutputDeviceConnectionException: public std::runtime_error
{
public:
  OutputDeviceConnectionException(const std::string& message)
    : std::runtime_error(message) {}
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

class WriteLimitReachedException: public std::logic_error
{
public:
	WriteLimitReachedException(const std::string& message): std::logic_error(message) {}
};

}
