#include "core/writable_channel.h"

#include <cstdint>
#include <string>

using namespace resonance_core;


template<typename T>
WritableChannel<T>::WritableChannel(T* current_position, int difference, int limit)
	: m_current_position((char*) current_position),
	m_difference(difference),
	m_limit(limit) {}


template<typename T>
WritableChannel<T>&
	WritableChannel<T>::operator<<(T sample)
{
	if (limit_reached())
	{
		throw WriteLimitReachedException(
			"Cannot write more than " + std::to_string(m_limit) + " samples to this channel"
		);
	}

	T* typed_position = (T*) m_current_position;

	*typed_position = sample;

	m_current_position += m_difference;
	m_used++;

	return *this;
}


template<typename T>
bool
	WritableChannel<T>::limit_reached()
{
	return m_used >= m_limit;
}


template class resonance_core::WritableChannel<int8_t>;
template class resonance_core::WritableChannel<int16_t>;
//template class resonance_core::WritableChannel<int24_t>;
template class resonance_core::WritableChannel<int32_t>;

static_assert(sizeof(float) == 4, "Must use 32-bit floats");
template class resonance_core::WritableChannel<float>;

static_assert(sizeof(double) == 8, "Must use 64-bit doubles");
template class resonance_core::WritableChannel<double>;
