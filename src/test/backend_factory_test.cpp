#include <gtest/gtest.h>
#include "core/backend_factory.h"

#include <memory>
#include <string>
#include <unordered_set>

#include "core/audio_backend.h"

#include "mock_backends/audio_backend.h"

using namespace resonance_core;


using BackendConstructor =
  std::function<std::unique_ptr<mock_backends::AudioBackend>()>;

using CoreBackendPtr = std::unique_ptr<AudioBackend>;
using MockBackendPtr = std::unique_ptr<mock_backends::AudioBackend>;


static BackendConstructor
  make_constructor(int id)
{
  return [id]()
  {
    return std::make_unique<mock_backends::AudioBackend>(id);
  };
}


static MockBackendPtr
  cast_to_mocked_backend(CoreBackendPtr backend)
{
  return MockBackendPtr(
    static_cast<mock_backends::AudioBackend*>(backend.release())
  );
}


TEST(BackendFactoryTest, BackendNamesEmpty)
{
  const BackendFactory factory;

  std::unordered_set<std::string> names = factory.get_backend_names();

  EXPECT_TRUE(names.empty());
}


TEST(BackendFactoryTest, ConstructsRegisteredBackend)
{
  BackendFactory factory;

  const std::string backend_name = "Mock Backend 0";

  factory.register_backend(backend_name, make_constructor(0));

  MockBackendPtr backend = cast_to_mocked_backend(
    factory.construct_backend(backend_name)
  );

  EXPECT_EQ(0, backend->get_id());
}


TEST(BackendFactoryTest, ThrowsInvalidBackendNameWhenNotRegistered)
{
  BackendFactory factory;

  EXPECT_THROW(
    factory.construct_backend("Non-Existant Backend"),
    InvalidBackendNameException
  );
}


TEST(BackendFactoryTest, ThrowsDuplicateBackendWhenNameDuplicated)
{
  BackendFactory factory;

  const std::string backend_name = "Mock Backend 0";

  factory.register_backend(backend_name, make_constructor(0));

  EXPECT_THROW(
    factory.register_backend(backend_name, make_constructor(1)),
    DuplicateBackendException
  );
}


TEST(BackendFactoryTest, ReturnsBackendNames)
{
  BackendFactory factory;

  const int backend_count = 5;
  const std::string backend_prefix = "Mock Backend ";
  std::unordered_set<std::string> expected_names;

  for (int backend_index = 0; backend_index < backend_count; backend_index++)
  {
    const std::string backend_name = backend_prefix + std::to_string(backend_index);

    expected_names.insert(backend_name);
    factory.register_backend(backend_name, make_constructor(backend_index));
  }

  std::unordered_set<std::string> actual_names = factory.get_backend_names();

  EXPECT_EQ(expected_names, actual_names);
}
