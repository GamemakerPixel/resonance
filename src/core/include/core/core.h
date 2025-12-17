#pragma once

#include <functional>
#include <memory>
#include <unordered_set>

#include "exceptions.h"

namespace resonance_core
{

class AbstractDepender
{
private:
  std::vector<std::function<void()>> m_deconstruction_callbacks;

public:
  void
    subscribe_to_deconstruction(std::function<void()> callback);

  virtual
    ~AbstractDepender();
};

template <typename T>
class AbstractSubscriptionPtr
{
private:
  std::shared_ptr<T> m_shared = nullptr;
  const std::weak_ptr<T> m_weak;
  int m_living_depender_count = 0;

public:
  AbstractSubscriptionPtr(std::shared_ptr<T> object);

  void
    subscribe_to_depender(AbstractDepender& depender);

  std::weak_ptr<T>
    get_object() const;

private:
  void
    on_depender_deconstructed();
};

enum class AudioChannelId
{
  LEFT,
  RIGHT,
  CENTER,
  LFE,
  BACK_LEFT,
  BACK_RIGHT,
  FRONT_LEFT_CENTER,
  FRONT_RIGHT_CENTER,
  BACK_CENTER,
  SIDE_LEFT,
  SIDE_RIGHT,
  TOP_CENTER,
  TOP_FRONT_LEFT,
  TOP_FRONT_CENTER,
  TOP_FRONT_RIGHT,
  TOP_BACK_LEFT,
  TOP_BACK_CENTER,
  TOP_BACK_RIGHT,
  AUX,
};

struct AudioChannelLayout
{
	static const std::unordered_map<AudioChannelId, std::string> id_names;

  std::vector<AudioChannelId> m_channel_ids;

  AudioChannelLayout(std::vector<AudioChannelId> channel_ids);

  bool
    operator==(const AudioChannelLayout& other) const;
  
  bool
    operator!=(const AudioChannelLayout& other) const;

	std::string
		to_string() const;
};

namespace standard_layouts
{
  extern const AudioChannelLayout mono;
  extern const AudioChannelLayout stereo;
}


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

struct AudioInterfaceSpec
{
  const AudioDataType m_data_type;
  const AudioChannelLayout m_layout;
  const unsigned int m_sample_rate;

  AudioInterfaceSpec(
    AudioDataType data_type,
    AudioChannelLayout layout,
    unsigned int sample_rate
  );

  bool
    operator==(const AudioInterfaceSpec& other) const;

  bool
    operator!=(const AudioInterfaceSpec& other) const;
};


class AudioOutputStream: public AbstractDepender
{
public:
  virtual
    ~AudioOutputStream() = default;
};

class AudioOutputDevice: public AbstractDepender
{
public:
  virtual
    ~AudioOutputDevice() = default;

  virtual std::unique_ptr<AudioOutputStream>
    create_stream(const AudioInterfaceSpec& spec) const = 0;

  virtual bool
    is_spec_compatable(const AudioInterfaceSpec& spec) const = 0;
};


class AudioBackend {
public:
  virtual
    ~AudioBackend() = default;

  virtual std::unordered_set<std::string>
    get_output_device_names() const = 0;

  virtual std::unique_ptr<AudioOutputDevice>
    create_output_device(const std::string& name) const = 0;
};

using AudioBackendConstructor = std::function<std::unique_ptr<AudioBackend>()>;

class BackendFactory
{
private:
  std::unordered_map<std::string, AudioBackendConstructor> m_backend_constructors;

public:
  void
    register_backend(std::string name, AudioBackendConstructor constructor);

  bool
    is_backend_supported(const std::string& name) const;

  std::unordered_set<std::string>
    get_backend_names() const;

  std::unique_ptr<AudioBackend>
    construct_backend(const std::string& backend_name) const;
};

class BackendLoader
{
private:
  const std::shared_ptr<const BackendFactory> m_factory;

  std::unordered_map<std::string, AbstractSubscriptionPtr<AudioBackend>> m_backends;
  std::unordered_map<
    std::string, std::unordered_map<
      std::string,
      AbstractSubscriptionPtr<AudioOutputDevice>
    >
  > m_output_devices;

public:
  BackendLoader(std::shared_ptr<const BackendFactory> factory);

  std::shared_ptr<AudioBackend>
    load_backend(const std::string& backend);

  std::shared_ptr<AudioOutputDevice>
    load_output_device(const std::string& backend, const std::string& device);

  std::unique_ptr<AudioOutputStream>
    create_output_stream(
      const std::string& backend,
      const std::string& device,
      const AudioInterfaceSpec& spec
    );
};

class BackendManager
{
private:
  const std::shared_ptr<const BackendFactory> m_factory;
  const std::unique_ptr<BackendLoader> m_loader;

public:
  BackendManager(std::unique_ptr<const BackendFactory> factory);

  std::unordered_set<std::string>
    get_backend_names() const;

  std::unordered_set<std::string>
    get_output_device_names(const std::string& backend_name);

	bool
		is_spec_compatable_with_output_device(
			const std::string& backend,
			const std::string& device,
			const AudioInterfaceSpec& spec
		);

  std::unique_ptr<AudioOutputStream>
    get_stream(
      const std::string& backend,
      const std::string& device,
      const AudioInterfaceSpec& spec
    );
};

template<typename T>
class WritableChannel
{
	const int m_difference;
	const int m_limit;
	char* m_current_position;
	int m_used = 0;

public:
	WritableChannel(T* current_position, int difference, int limit);

	WritableChannel&
		operator<<(T sample);

	bool
		limit_reached();
};

}

