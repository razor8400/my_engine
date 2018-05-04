#pragma once

#include <iostream>
#include <sstream>

namespace engine
{
	class logger
	{
	public:
		logger();
		~logger();

		logger& operator<<(bool val);
		logger& operator<<(short val);
		logger& operator<<(unsigned short val);
		logger& operator<<(int val);
		logger& operator<<(unsigned int val);
		logger& operator<<(long val);
		logger& operator<<(unsigned long val);
		logger& operator<<(long long val);
		logger& operator<<(unsigned long long val);
		logger& operator<<(float val);
		logger& operator<<(double val);
		logger& operator<<(long double val);
		logger& operator<<(const char* val);
		logger& operator<<(const std::string& val);
	private:
		std::stringstream m_buffer;
	};
}