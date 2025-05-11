#pragma once

#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>


namespace resonance_core
{

class AudioBackend;

class BackendFactory
{
private:
  using AudioBackendConstructor = std::function<std::unique_ptr<AudioBackend>()>;

  std::unordered_map<std::string, AudioBackendConstructor> m_backend_constructors;

public:
  void
    register_backend(std::string name, AudioBackendConstructor constructor);

  std::vector<std::string>
    get_backend_names() const;

  std::unique_ptr<AudioBackend>
  construct_backend(const std::string& backend_name) const;
};

class InvalidBackendNameException: public std::logic_error
{
public:
  InvalidBackendNameException(const std::string& message)
    : std::logic_error(message) {}
};

class DuplicateBackendException: public std::logic_error
{
public:
  DuplicateBackendException(const std::string& message)
    : std::logic_error(message) {}
};

}
