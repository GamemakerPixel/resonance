#pragma once

#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>


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

  bool
    is_backend_supported(const std::string& name) const;

  std::unordered_set<std::string>
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

class BackendConstructionException: public std::runtime_error
{
public:
  BackendConstructionException(const std::string& message)
    : std::runtime_error(message) {}
};

}
