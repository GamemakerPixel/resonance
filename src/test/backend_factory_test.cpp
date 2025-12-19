#include <gtest/gtest.h>
#include "core/core.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_set>

#include "mock_backends/mock_backends.h"

#include "test_helpers.h"

using namespace resonance_core;


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

  factory.register_backend(backend_name, test_help::make_constructor(0));

  test_help::MockBackendUPtr backend = test_help::cast_to_mocked_backend(
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

  factory.register_backend(backend_name, test_help::make_constructor(0));

  EXPECT_THROW(
    factory.register_backend(backend_name, test_help::make_constructor(1)),
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
    factory.register_backend(backend_name, test_help::make_constructor(backend_index));
  }

  std::unordered_set<std::string> actual_names = factory.get_backend_names();

  EXPECT_EQ(expected_names, actual_names);
}


TEST(BackendFactoryTest, ThrowsBackendConstructionWhenNull)
{
  BackendFactory factory;

  const std::string backend_name = "Mock Backend 0";

  const test_help::BackendConstructor constructor([]()
  {
    return test_help::MockBackendUPtr(nullptr);
  });

  factory.register_backend(backend_name, constructor);

  EXPECT_THROW(
    factory.construct_backend(backend_name),
    BackendConstructionException
  );
}


TEST(BackendFactoryTest, ThrowsBackendConstructionWhenConstructorThrowsException)
{
  BackendFactory factory;

  const std::string backend_name = "Mock Backend -1";

  // Mocked AudioBackend is set up to throw a std::runtime_error when id is below 0.
  factory.register_backend(backend_name, test_help::make_constructor(-1));

  EXPECT_THROW(
    factory.construct_backend(backend_name),
    BackendConstructionException
  );
}


TEST(BackendFactoryTest, ShowsRegisteredBackendAsSupported)
{
  BackendFactory factory;

  const std::string backend_name = "Mock Backend 0";

  factory.register_backend(backend_name, test_help::make_constructor(0));

  EXPECT_TRUE(factory.is_backend_supported(backend_name));
}


TEST(BackendFactoryTest, ShowsNotRegisteredBackendAsNotSupported)
{
  BackendFactory factory;

  const std::string backend_name = "Mock Backend 0";

  EXPECT_FALSE(factory.is_backend_supported(backend_name));
}
