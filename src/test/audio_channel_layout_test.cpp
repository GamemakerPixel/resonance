#include <gtest/gtest.h>
#include "core/audio_channel_layout.h"

using namespace resonance_core;


TEST(AudioChannelLayoutTest, NotEqualWhenLayoutVectorDiffers)
{
	const AudioChannelLayout layout_a(
		{
			AudioChannelId::LEFT,
			AudioChannelId::RIGHT,
		}
	);

	const AudioChannelLayout layout_b(
		{
			AudioChannelId::RIGHT,
			AudioChannelId::LEFT,
		}
	);

	EXPECT_FALSE(layout_a == layout_b);
	EXPECT_TRUE(layout_a != layout_b);
}


TEST(AudioChannelLayoutTest, EqualWhenLayoutVectorSame)
{
	const AudioChannelLayout layout_a(
		{
			AudioChannelId::LEFT,
			AudioChannelId::RIGHT,
		}
	);

	const AudioChannelLayout layout_b(
		{
			AudioChannelId::LEFT,
			AudioChannelId::RIGHT,
		}
	);

	EXPECT_TRUE(layout_a == layout_b);
	EXPECT_FALSE(layout_a != layout_b);
}


TEST(AudioChannelLayoutTest, ConvertsToString)
{
	const AudioChannelLayout layout(
		{
			AudioChannelId::LEFT,
			AudioChannelId::RIGHT,
		}
	);

	EXPECT_EQ(
		"Layout: [Left, Right]",
		layout.to_string()
	);
}
