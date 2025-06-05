#include <gtest/gtest.h>
#include "core/writable_channel.h"

using namespace resonance_core;


TEST(WritableChannelTest, WritesToCurrentPosition)
{
	int32_t	num;
	int32_t expected = 5;

	WritableChannel<int32_t> channel(&num, sizeof(int32_t), 1);

	channel << expected;

	EXPECT_EQ(expected, num);
}


TEST(WritableChannelTest, WritesToSecondPositionUsingDifference)
{
	int32_t	buffer[3];
	int32_t expected = 5;

	WritableChannel<int32_t> channel(buffer, sizeof(int32_t) * 2, 2);

	channel << 0 << expected;

	EXPECT_EQ(expected, buffer[2]);
}


TEST(WritableChannelTest, ThrowsWriteLimitReachedWhenLimitExceeded)
{
	int32_t	buffer[2];

	WritableChannel<int32_t> channel(buffer, sizeof(int32_t), 1);

	EXPECT_THROW(
		channel << 0 << 0,
		WriteLimitReachedException
	);
}


TEST(WritableChannelTest, DoesntWritePastLimit)
{
	int32_t	buffer[2];
	int32_t not_expected = 5;

	buffer[1] = 0;

	WritableChannel<int32_t> channel(buffer, sizeof(int32_t), 1);

	try
	{
		channel << 0 << not_expected;
	}
	catch (const WriteLimitReachedException&) {}

	EXPECT_NE(not_expected, buffer[1]);
}


TEST(WritableChannelTest, LimitNotReachedWhenNotEnoughWritesYet)
{
	float buffer[2];

	WritableChannel<float> channel(buffer, sizeof(float), 2);

	channel << 0.0f;

	EXPECT_FALSE(channel.limit_reached());
}


TEST(WritableChannelTest, LimitReachedWhenEnoughWrites)
{
	float buffer[2];

	WritableChannel<float> channel(buffer, sizeof(float), 2);

	channel << 0.0f << 0.0f;

	EXPECT_TRUE(channel.limit_reached());
}
