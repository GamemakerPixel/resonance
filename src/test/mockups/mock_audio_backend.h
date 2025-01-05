#pragma once

#include "core/audio_backend.h"


class MockBackend : public AudioBackend
{
public:
  MockBackend(std::unordered_set<std::string> avaliable_backends);

  std::unordered_set<std::string> get_avaliable_backends() const override;
  void connect_to_backend(const std::string& backend_name) override;
  std::string get_connected_backend_name() const override;
};
