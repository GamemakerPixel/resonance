#include <gtest/gtest.h>
#include "core/abstract_subscription_ptr.h"

#include <memory>

#include "core/abstract_depender.h"

#include "mock_backends/audio_backend.h"


using namespace resonance_core;


TEST(AbstractSubscriptionPtrTest, ThrowsNullDependeeWhenConstructionArgumentIsNull)
{
  std::shared_ptr<mock_backends::AudioBackend> null_backend = nullptr;

  EXPECT_THROW(
    std::make_unique<AbstractSubscriptionPtr<AudioBackend>>(null_backend),
    NullDependeeException
  );
}


TEST(AbstractSubscriptionPtrTest, DoesntTakeOwnershipOnConstruction)
{
  std::weak_ptr<mock_backends::AudioBackend> weak_backend;
  std::unique_ptr<AbstractSubscriptionPtr<AudioBackend>> sub_ptr;

  {
    auto shared_backend = std::make_shared<mock_backends::AudioBackend>(0, 0);

    weak_backend = shared_backend;

    sub_ptr = std::make_unique<AbstractSubscriptionPtr<AudioBackend>>(shared_backend);
  }

  EXPECT_TRUE(weak_backend.expired());
}


TEST(AbstractSubscriptionPtrTest, TakesOwnershipAfterSubscribedToDepender)
{
  std::weak_ptr<mock_backends::AudioBackend> weak_backend;
  std::unique_ptr<AbstractSubscriptionPtr<AudioBackend>> sub_ptr;

  AbstractDepender depender;

  {
    auto shared_backend = std::make_shared<mock_backends::AudioBackend>(0, 0);

    weak_backend = shared_backend;

    sub_ptr = std::make_unique<AbstractSubscriptionPtr<AudioBackend>>(shared_backend);

    sub_ptr->subscribe_to_depender(depender);
  }

  EXPECT_FALSE(weak_backend.expired());
}


TEST(
  AbstractSubscriptionPtrTest,
  ThrowsDependeeExpiredWhenGivenDependerAfterDependeeExpires
) {
  std::weak_ptr<mock_backends::AudioBackend> weak_backend;
  std::unique_ptr<AbstractSubscriptionPtr<AudioBackend>> sub_ptr;

  {
    auto shared_backend = std::make_shared<mock_backends::AudioBackend>(0, 0);

    weak_backend = shared_backend;

    sub_ptr = std::make_unique<AbstractSubscriptionPtr<AudioBackend>>(shared_backend);
  }
  
  AbstractDepender depender;

  EXPECT_THROW(
    sub_ptr->subscribe_to_depender(depender),
    DependeeExpiredException
  );
}


TEST(
  AbstractSubscriptionPtrTest,
  ReleasesOwnershipAfterAllSubscribedDependersDeconstruct
) {
  std::weak_ptr<mock_backends::AudioBackend> weak_backend;
  std::unique_ptr<AbstractSubscriptionPtr<AudioBackend>> sub_ptr;

  {
    auto shared_backend = std::make_shared<mock_backends::AudioBackend>(0, 0);

    weak_backend = shared_backend;

    sub_ptr = std::make_unique<AbstractSubscriptionPtr<AudioBackend>>(shared_backend);

    AbstractDepender depender;
    sub_ptr->subscribe_to_depender(depender);
  }

  EXPECT_TRUE(weak_backend.expired());
}


TEST(
  AbstractSubscriptionPtrTest,
  DoesntReleasesOwnershipAfterLessThanAllSubscribedDependersDeconstruct
) {
  std::weak_ptr<mock_backends::AudioBackend> weak_backend;
  std::unique_ptr<AbstractSubscriptionPtr<AudioBackend>> sub_ptr;

  AbstractDepender alive_depender;

  {
    auto shared_backend = std::make_shared<mock_backends::AudioBackend>(0, 0);

    weak_backend = shared_backend;

    sub_ptr = std::make_unique<AbstractSubscriptionPtr<AudioBackend>>(shared_backend);

    AbstractDepender depender;
    sub_ptr->subscribe_to_depender(depender);
    sub_ptr->subscribe_to_depender(alive_depender);
  }

  EXPECT_FALSE(weak_backend.expired());
}


TEST(
  AbstractSubscriptionPtrTest,
  RegainsOwnershipAfterAllSubscribedDependersDeconstructButNewOneAddedWhileObjectAlive
) {
  std::weak_ptr<mock_backends::AudioBackend> weak_backend;
  std::unique_ptr<AbstractSubscriptionPtr<AudioBackend>> sub_ptr;

  AbstractDepender alive_depender;

  {
    auto shared_backend = std::make_shared<mock_backends::AudioBackend>(0, 0);

    weak_backend = shared_backend;

    sub_ptr = std::make_unique<AbstractSubscriptionPtr<AudioBackend>>(shared_backend);

    {
      AbstractDepender depender;
      sub_ptr->subscribe_to_depender(depender);
      // Will drop reference count to 0, so sub_ptr will drop ownership, but since
      // shared_backend is still in scope, adding another afterwards should cause it to
      // regain ownership.
    }

    sub_ptr->subscribe_to_depender(alive_depender);
  }

  EXPECT_FALSE(weak_backend.expired());
}
