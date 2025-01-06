#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#include "core/audio_backend.h"


namespace AudioOutputExceptions
{
  class no_requested_backends : public std::runtime_error
  {
  public:
    no_requested_backends() :
      runtime_error("No requested backends were avaliable") {}
  };
}


class AudioOutput
{
private:
  AudioBackend& m_backend;
  const std::vector<std::string>& m_connection_order;

public:
  AudioOutput(AudioBackend& backend, const std::vector<std::string>& connection_order);

  void connect_backend();
  std::string get_connected_backend() const;
};
