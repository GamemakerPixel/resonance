#include "audio_data_type.h"

#include <string>
#include <unordered_map>

using namespace resonance_core;


static const std::unordered_map<AudioDataType, std::string> type_strings =
{
    {AudioDataType::INT8, "8-Bit Integer"},
    {AudioDataType::INT16, "16-Bit Integer"},
    {AudioDataType::INT24, "24-Bit Integer"},
    {AudioDataType::INT32, "32-Bit Integer"},
    {AudioDataType::FLOAT32, "32-Bit Float"},
    {AudioDataType::FLOAT64, "64-Bit Float"},
};


std::string resonance_core::audio_data_type_to_string(AudioDataType type)
{
	return type_strings.at(type);
}
