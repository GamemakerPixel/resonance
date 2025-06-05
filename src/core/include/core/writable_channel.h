#pragma once

#include <stdexcept>
#include <string>


namespace resonance_core
{

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


class WriteLimitReachedException: public std::logic_error
{
public:
	WriteLimitReachedException(const std::string& message): std::logic_error(message) {}
};

}
