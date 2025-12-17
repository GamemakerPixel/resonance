#include "backend_factory.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "audio_backend.h"

using namespace resonance_core;

void
  BackendFactory::register_backend(
    std::string name,
    AudioBackendConstructor constructor
  )
{
  if (m_backend_constructors.contains(name))
  {
    throw DuplicateBackendException(
      "Backend named " + name + " has already been registered"
    );
  }

  m_backend_constructors.emplace(name, constructor);
}

bool
  BackendFactory::is_backend_supported(const std::string& name) const
{
  return m_backend_constructors.contains(name);
}

std::unordered_set<std::string>
  BackendFactory::get_backend_names() const
{
  std::unordered_set<std::string> names;

  for (const auto& [name, _]: m_backend_constructors)
  {
    names.insert(name);
  }

  return names;
}

std::unique_ptr<AudioBackend>
  BackendFactory::construct_backend(const std::string& backend_name) const
{
  if (!m_backend_constructors.contains(backend_name))
  {
    throw InvalidBackendNameException(backend_name + " is not a known backend");
  }

  try
  {
    std::unique_ptr<AudioBackend> backend = m_backend_constructors.at(backend_name)();

    if (!backend)
    {
      throw BackendConstructionException(
        "Created backend (" + backend_name + ") was nullptr"
      );
    }

    return backend;
  }
  catch (const std::exception& exception)
  {
    throw BackendConstructionException(
      "An exception was thrown while constructing \"" + backend_name + "\":\n"
      + exception.what()
    );
  }
  catch (...)
  {
    throw BackendConstructionException(
      "An exception was thrown while constructing \"" + backend_name + "\"."
    );
  }
}
