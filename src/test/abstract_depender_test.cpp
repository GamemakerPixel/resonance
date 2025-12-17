#include <gtest/gtest.h>
#include "core/core.h"

using namespace resonance_core;


TEST(AbstractDependerTest, NotNotifiedWhenNotDeleted)
{
  int notification_count = 0;

  std::function<void()> callback = [&notification_count]()
  {
    notification_count++;
  };

  AbstractDepender depender;

  depender.subscribe_to_deconstruction(callback);

  EXPECT_EQ(0, notification_count);
}


TEST(AbstractDependerTest, NotifiedWhenDeleted)
{
  int notification_count = 0;

  std::function<void()> callback = [&notification_count]()
  {
    notification_count++;
  };

  {
    AbstractDepender depender;

    depender.subscribe_to_deconstruction(callback);
    depender.subscribe_to_deconstruction(callback);
  }

  EXPECT_EQ(2, notification_count);
}
