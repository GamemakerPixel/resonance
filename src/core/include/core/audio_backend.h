#pragma once

#include <string>
#include <unordered_set>


class AudioBackend
{
public:
  static const std::string NO_BACKEND = "none";

  virtual ~AudioBackend() = default;

  virtual std::unordered_set<std::string> get_avaliable_backends() const = 0;
  /*
  virtual void connect_to_backend(const std::string& backend_name) = 0;
  virtual std::string get_connected_backend_name() const = 0;
  */
};
