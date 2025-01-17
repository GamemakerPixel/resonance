#pragma once

#include <stdexcept>
#include <string>
#include <unordered_set>


namespace BackendExceptions
{
  class unavaliable_backend : public std::invalid_argument
  {
  public:
    unavaliable_backend(const std::string& backend_name) :
      invalid_argument("Backend \"" + backend_name + "\" is not avaliable") {}
  };

  class backend_connect_failure : public std::runtime_error
  {
  public:
    backend_connect_failure(const std::string& description) :
      runtime_error(description) {}
  };
}


class AudioBackend
{
public:
  static const std::string NO_BACKEND;

  virtual ~AudioBackend() = default;

  virtual std::unordered_set<std::string> get_avaliable_backends() const = 0;
  virtual void connect_to_backend(const std::string& backend_name) = 0;
  virtual std::string get_connected_backend_name() const = 0;
};
