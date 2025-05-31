#pragma once

#include <string>


namespace resonance_core
{

enum class AudioDataType
{
  INT8,
  INT16,
  INT24,
  INT32,
  FLOAT32,
  FLOAT64,
};

std::string audio_data_type_to_string(AudioDataType type);

}

