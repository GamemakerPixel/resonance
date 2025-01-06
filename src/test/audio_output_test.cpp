#include <gtest/gtest.h>
#include "core/audio_output.h"

#include "mockups/mock_audio_backend.h"


TEST(AudioOutputTest, ConnectsToFirstBackend)
{
  std::unordered_set<std::string> avaliable_backends = 
  {
    "First Backend",
    "Second Backend",
  };

  std::vector<std::string> connection_order = 
  {
    "First Backend",
    "Second Backend",
  };

  MockAudioBackend backend(avaliable_backends);
  AudioOutput audio_output(backend, connection_order);

  audio_output.connect_backend();

  EXPECT_EQ(audio_output.get_connected_backend(), "First Backend");
}


