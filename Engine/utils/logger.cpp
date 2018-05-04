#include "common.h"
#include "logger.h"

#include <iomanip>
#include <ctime>

#ifdef _MSC_VER
#include <windows.h>
#define LOG(text)\
OutputDebugStringA(text);
#else
#define LOG(text)\
	std::cout << text;
#endif

namespace engine
{
	logger::logger()
	{
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		m_buffer << std::put_time(&tm, "%d.%m.%Y %H:%M:%S: ");
	}

	logger::~logger()
	{
		m_buffer << std::endl;
		LOG(m_buffer.str().c_str())
	}

	logger& logger::operator<<(bool val)
	{
		m_buffer << val;
		return *this;
	}

	logger& logger::operator<<(short val)
	{
		m_buffer << val;
		return *this;
	}

	logger& logger::operator<<(unsigned short val)
	{
		m_buffer << val;
		return *this;
	}

	logger& logger::operator<<(int val)
	{
		m_buffer << val;
		return *this;
	}

	logger& logger::operator<<(unsigned int val)
	{
		m_buffer << val;
		return *this;
	}

	logger& logger::operator<<(long val)
	{
		m_buffer << val;
		return *this;
	}

	logger& logger::operator<<(unsigned long val)
	{
		m_buffer << val;
		return *this;
	}

	logger& logger::operator<<(long long val)
	{
		m_buffer << val;
		return *this;
	}

	logger& logger::operator<<(unsigned long long val)
	{
		m_buffer << val;
		return *this;
	}

	logger& logger::operator<<(float val)
	{
		m_buffer << val;
		return *this;
	}

	logger& logger::operator<<(double val)
	{
		m_buffer << val;
		return *this;
	}

	logger& logger::operator<<(long double val)
	{
		m_buffer << val;
		return *this;
	}

	logger& logger::operator<<(const char* val)
	{
		m_buffer << val;
		return *this;
	}

	logger & logger::operator<<(const std::string& val)
	{
		m_buffer << val;
		return *this;
	}
}