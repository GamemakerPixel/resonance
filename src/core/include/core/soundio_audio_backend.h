#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>

#include <soundio/soundio.h>

#include "core/audio_backend.h"


class SoundioAudioBackend : public AudioBackend
{
private:
  static const std::unordered_map<SoundIoBackend, std::string> BACKEND_IDENTIFIERS;

  const std::unique_ptr<SoundIo, void(*)(SoundIo*)> m_context;
  const std::unordered_map<std::string, SoundIoBackend> m_avaliable_backends;

public:
  SoundioAudioBackend();

  std::unordered_set<std::string> get_avaliable_backends() const override;
  void connect_to_backend(const std::string& backend_name) override;
  std::string get_connected_backend_name() const override;

private:
  static std::unordered_map<std::string, SoundIoBackend>
  query_avaliable_backends(SoundIo* context);
};
