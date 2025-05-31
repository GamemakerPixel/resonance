#include <gtest/gtest.h>
#include "core/audio_data_type.h"

using namespace resonance_core;


TEST(AudioDataTypeTest, ConvertsTypeToString)
{
	EXPECT_EQ(
		"24-Bit Integer",
		audio_data_type_to_string(AudioDataType::INT24)
	);
}

