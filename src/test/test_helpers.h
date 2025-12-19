#pragma once

#include <functional>
#include <memory>

#include "mock_backends/mock_backends.h"


namespace resonance_core
{

class AudioBackend;
class AudioOutputDevice;
class AudioOutputStream;

}


namespace mock_backends
{

class AudioOutputDevice;
class AudioOutputStream;

}


namespace test_help
{

using BackendConstructor =
  std::function<std::unique_ptr<mock_backends::AudioBackend>()>;

using CoreBackendUPtr = std::unique_ptr<resonance_core::AudioBackend>;
using MockBackendUPtr = std::unique_ptr<mock_backends::AudioBackend>;
using CoreBackendSPtr = std::shared_ptr<resonance_core::AudioBackend>;
using MockBackendSPtr = std::shared_ptr<mock_backends::AudioBackend>;
using CoreOutputDeviceUPtr = std::unique_ptr<resonance_core::AudioOutputDevice>;
using MockOutputDeviceUPtr = std::unique_ptr<mock_backends::AudioOutputDevice>;
using CoreOutputDeviceSPtr = std::shared_ptr<resonance_core::AudioOutputDevice>;
using MockOutputDeviceSPtr = std::shared_ptr<mock_backends::AudioOutputDevice>;
using CoreOutputStreamUPtr = std::unique_ptr<resonance_core::AudioOutputStream>;
using MockOutputStreamUPtr = std::unique_ptr<mock_backends::AudioOutputStream>;
using CoreOutputStreamSPtr = std::shared_ptr<resonance_core::AudioOutputStream>;
using MockOutputStreamSPtr = std::shared_ptr<mock_backends::AudioOutputStream>;


static BackendConstructor
  make_constructor(int id, int device_count)
{
  return [id, device_count]()
  {
    return std::make_unique<mock_backends::AudioBackend>(id, device_count);
  };
}


static BackendConstructor
  make_constructor(int id)
{
  return make_constructor(id, 0);
}


static MockBackendUPtr
  cast_to_mocked_backend(CoreBackendUPtr backend)
{
  return MockBackendUPtr(
    dynamic_cast<mock_backends::AudioBackend*>(backend.release())
  );
}


static MockOutputStreamUPtr
  cast_to_mocked_stream(CoreOutputStreamUPtr stream)
{
  return MockOutputStreamUPtr(
    dynamic_cast<mock_backends::AudioOutputStream*>(stream.release())
  );
}

}
