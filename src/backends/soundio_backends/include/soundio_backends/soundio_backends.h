#pragma once

#include <core/core.h>
#include <soundio/soundio.h>


namespace soundio_backends
{

void register_backends(resonance_core::BackendFactory& factory);

class AudioBackend: public resonance_core::AudioBackend
{
private:
  const std::unique_ptr<SoundIo, void(*)(SoundIo*)> m_context;

public:
  AudioBackend(SoundIoBackend backend);
  ~AudioBackend();

  std::unordered_set<std::string>
    get_output_device_names() const override;
  
  std::unique_ptr<resonance_core::AudioOutputDevice>
    create_output_device(const std::string& name) const override;
};

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

class AudioOutputDevice: public resonance_core::AudioOutputDevice
{
private:
  const std::unique_ptr<SoundIoDevice, void(*)(SoundIoDevice*)> m_device;

public:
  AudioOutputDevice(std::unique_ptr<SoundIoDevice, void(*)(SoundIoDevice*)> device);

  std::unique_ptr<resonance_core::AudioOutputStream>
    create_stream(const resonance_core::AudioInterfaceSpec& spec) const override;
  
  bool
    is_spec_compatable(const resonance_core::AudioInterfaceSpec& spec) const override;

private:
  void
    validate_spec(const resonance_core::AudioInterfaceSpec& spec) const;
    
  SoundIoFormat
    negotiate_compatable_format(resonance_core::AudioDataType type) const;
};

class AudioOutputStream: public resonance_core::AudioOutputStream
{
private:
  std::unique_ptr<SoundIoOutStream, void(*)(SoundIoOutStream*)> m_stream;

public:
  AudioOutputStream(
    std::unique_ptr<SoundIoOutStream, void(*)(SoundIoOutStream*)> stream,
    const AudioInterfaceSpecSoundIo& spec
  );
};

}
