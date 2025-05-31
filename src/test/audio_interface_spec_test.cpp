#include <gtest/gtest.h>
#include "core/audio_interface_spec.h"

using namespace resonance_core;


TEST(AudioInterfaceSpecTest, SpecsNotEqualWhenDataTypeDiffers)
{
	AudioInterfaceSpec spec_a(
		AudioDataType::INT8,
		standard_layouts::stereo,
		44100u
	);

	AudioInterfaceSpec spec_b(
		AudioDataType::INT16,
		standard_layouts::stereo,
		44100u
	);

	// Using boolean expects in order to test false conditions of operators, plus we're
	// testing the operators, not the values.
	EXPECT_FALSE(spec_a == spec_b);
	EXPECT_TRUE(spec_a != spec_b);
}


TEST(AudioInterfaceSpecTest, SpecsNotEqualWhenChannelLayoutDiffers)
{
	AudioInterfaceSpec spec_a(
		AudioDataType::INT16,
		standard_layouts::mono,
		44100u
	);

	AudioInterfaceSpec spec_b(
		AudioDataType::INT16,
		standard_layouts::stereo,
		44100u
	);

	EXPECT_FALSE(spec_a == spec_b);
	EXPECT_TRUE(spec_a != spec_b);
}


TEST(AudioInterfaceSpecTest, SpecsNotEqualWhenSampleRateDiffers)
{
	AudioInterfaceSpec spec_a(
		AudioDataType::INT16,
		standard_layouts::stereo,
		48000u
	);

	AudioInterfaceSpec spec_b(
		AudioDataType::INT16,
		standard_layouts::stereo,
		44100u
	);

	EXPECT_FALSE(spec_a == spec_b);
	EXPECT_TRUE(spec_a != spec_b);
}


TEST(AudioInterfaceSpecTest, SpecsEqual)
{
	AudioInterfaceSpec spec_a(
		AudioDataType::INT16,
		standard_layouts::stereo,
		44100u
	);

	AudioInterfaceSpec spec_b(
		AudioDataType::INT16,
		standard_layouts::stereo,
		44100u
	);

	EXPECT_TRUE(spec_a == spec_b);
	EXPECT_FALSE(spec_a != spec_b);
}
