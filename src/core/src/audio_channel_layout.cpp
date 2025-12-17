#include "audio_channel_layout.h"


using namespace resonance_core;


const std::unordered_map<AudioChannelId, std::string> AudioChannelLayout::id_names =
{
	{AudioChannelId::LEFT, "Left"},
	{AudioChannelId::RIGHT, "Right"},
	{AudioChannelId::CENTER, "Center"},
	{AudioChannelId::LFE, "Low-Frequency Effects"},
	{AudioChannelId::BACK_LEFT, "Back Left"},
	{AudioChannelId::BACK_RIGHT, "Back Right"},
	{AudioChannelId::FRONT_LEFT_CENTER, "Front Left Center"},
	{AudioChannelId::FRONT_RIGHT_CENTER, "Front Right Center"},
	{AudioChannelId::BACK_CENTER, "Back Center"},
	{AudioChannelId::SIDE_LEFT, "Side Left"},
	{AudioChannelId::SIDE_RIGHT, "Side Right"},
	{AudioChannelId::TOP_CENTER, "Top Center"},
	{AudioChannelId::TOP_FRONT_LEFT, "Top Front Left"},
	{AudioChannelId::TOP_FRONT_CENTER, "Top Front Center"},
	{AudioChannelId::TOP_FRONT_RIGHT, "Top Front Right"},
	{AudioChannelId::TOP_BACK_LEFT, "Top Back Left"},
	{AudioChannelId::TOP_BACK_CENTER, "Top Back Center"},
	{AudioChannelId::TOP_BACK_RIGHT, "Top Back Right"},
	{AudioChannelId::AUX, "Auxiliary"},
};


AudioChannelLayout::AudioChannelLayout(std::vector<AudioChannelId> channel_ids)
  : m_channel_ids(channel_ids) {}


bool
  AudioChannelLayout::operator==(const AudioChannelLayout& other) const
{
  return m_channel_ids == other.m_channel_ids;
}


bool
  AudioChannelLayout::operator!=(const AudioChannelLayout& other) const
{
  return !operator==(other);
}


std::string
	AudioChannelLayout::to_string() const
{
	std::string result = "Layout: [";

	for (int id_index = 0; id_index < m_channel_ids.size(); id_index++)
	{
		AudioChannelId id = m_channel_ids.at(id_index);
		result += id_names.at(id);

		if (id_index != m_channel_ids.size() - 1)
		{
			result += ", ";
		}
	}

	result += "]";

	return result;
}


const AudioChannelLayout standard_layouts::mono({
  AudioChannelId::CENTER
});

const AudioChannelLayout standard_layouts::stereo({
  AudioChannelId::LEFT,
  AudioChannelId::RIGHT
});
