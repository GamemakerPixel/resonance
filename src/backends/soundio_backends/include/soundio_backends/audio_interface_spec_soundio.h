#pragma once

#include <array>
#include <soundio/soundio.h>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "core/audio_channel_layout.h"
#include "core/audio_data_type.h"
#include "core/audio_interface_spec.h"


namespace soundio_backends
{

struct AudioInterfaceSpecSoundIo
{
  static const std::unordered_map<
    resonance_core::AudioChannelId, SoundIoChannelId
  > channel_ids;

  static const std::unordered_map<
    resonance_core::AudioDataType, std::array<SoundIoFormat, 4>
  > formats;

  static const std::unordered_set<SoundIoFormat> unsigned_formats;
  static const std::unordered_set<SoundIoFormat> foreign_endian_formats;

  const SoundIoFormat m_format;
  const SoundIoChannelLayout m_layout;
  const int m_sample_rate;

  AudioInterfaceSpecSoundIo(
    const resonance_core::AudioInterfaceSpec& spec,
    bool unsigned_int,
    bool foreign_endian
  );
 
  AudioInterfaceSpecSoundIo(
    const resonance_core::AudioInterfaceSpec& spec
  );

  static const std::array<SoundIoFormat, 4>&
    get_compatable_formats(resonance_core::AudioDataType type);

  static bool
    is_unsigned(SoundIoFormat format);

  static bool
    is_foreign_endian(SoundIoFormat format);

private:
  static int
    core_sample_rate_to_soundio_sample_rate(unsigned int sample_rate);

  static SoundIoFormat
    core_type_to_soundio_format(
      resonance_core::AudioDataType type,
      bool unsigned_int,
      bool foreign_endian
    );

  static SoundIoChannelLayout
    core_layout_to_soundio_layout(const resonance_core::AudioChannelLayout& layout);
};

class InvalidSpecValuesException: public std::logic_error
{
public:
  InvalidSpecValuesException(const std::string& message)
    : std::logic_error(message) {}
};

}

