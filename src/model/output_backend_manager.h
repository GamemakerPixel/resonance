#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <soundio/soundio.h>

enum class OutputBackend
{
  NONE,
  JACK,
  PULSE_AUDIO,
  ALSA,
  CORE_AUDIO,
  WASAPI,
  DUMMY,
};


class OutputBackendManager
{
  public:
    OutputBackendManager();
    ~OutputBackendManager();
    std::vector<OutputBackend> get_avaliable_backends() const;
//    void connect_to_first_avaliable_backend();
    void connect_to_backend(OutputBackend backend);
//    OutputBackend get_connected_backend() const;
    std::string get_backend_name(OutputBackend backend) const;
  private:
    static const std::unordered_map<SoundIoBackend, OutputBackend> soundio_backend_conversion_map;
    static const std::unordered_map<OutputBackend, SoundIoBackend> reversed_backend_conversion_map;
    static const std::unordered_map<OutputBackend, std::string> backend_names;
    SoundIo* backend_context;
    OutputBackend connected_backend;
};
