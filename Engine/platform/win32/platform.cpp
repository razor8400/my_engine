#include "common.h"
#include "platform/platform.h"

namespace engine
{
	static const char* platform_code = "win32";

	platform& platform::instance()
	{
		static platform instance;
		return instance;
	}

	platform::platform()
	{

	}

	platform::~platform()
	{

	}

	const char* platform::get_platform_code() const
	{
		return platform_code;
	}
}