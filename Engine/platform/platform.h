#pragma once

namespace engine
{
	class platform
	{
	public:
		static platform& instance();

		const char* get_platform_code() const;
	private:
		platform();
		~platform();
	};
}
