#include <gtest/gtest.h>
#include "core/audio_output.h"

#include "mockups/mock_audio_backend.h"


class AudioOutputTest : public testing::Test
{
protected:
  static const std::unordered_set<std::string> AVALIABLE_BACKENDS;
  static const std::vector<std::string> CONNECTION_ORDER;

  MockAudioBackend m_backend;
  AudioOutput m_audio_output;

  AudioOutputTest() :
    m_backend(AVALIABLE_BACKENDS),
    m_audio_output(m_backend, CONNECTION_ORDER) {}
};


const std::unordered_set<std::string> AudioOutputTest::AVALIABLE_BACKENDS =
{
  "First Backend",
  "Second Backend",
};
const std::vector<std::string> AudioOutputTest::CONNECTION_ORDER =
{
  "First Backend",
  "Second Backend",
};


TEST_F(AudioOutputTest, ConnectsToFirstBackend)
{
  m_audio_output.connect_backend();

  EXPECT_EQ(m_audio_output.get_connected_backend(), "First Backend");
}


// Note that strings not in the avaliable backends will be treated as unavaliable
// and therefore covered by this test.
TEST_F(AudioOutputTest, ConnectsToFirstAvaliableBackendWhenPreferredUnavaliable)
{
  m_backend.set_backend_status("First Backend", BackendStatus::UNAVALIABLE);

  m_audio_output.connect_backend();

  EXPECT_EQ(m_audio_output.get_connected_backend(), "Second Backend");
}


TEST_F(AudioOutputTest, ThrowsNoAudioOutputExceptionWhenAllBackendsUnavaliable)
{
  m_backend.set_backend_status("First Backend", BackendStatus::UNAVALIABLE);
  m_backend.set_backend_status("Second Backend", BackendStatus::UNAVALIABLE);

  EXPECT_THROW(
    m_audio_output.connect_backend(),
    AudioOutputExceptions::no_requested_backends
  );
}


TEST_F(AudioOutputTest, ConnectsToFirstAvaliableBackendWhenPreferredErroring)
{
  m_backend.set_backend_status("First Backend", BackendStatus::ERROR);

  m_audio_output.connect_backend();

  EXPECT_EQ(m_audio_output.get_connected_backend(), "Second Backend");
}
