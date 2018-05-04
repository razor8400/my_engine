#include "common.h"
#include "platform/file_system/file_system.h"

#include <direct.h>

namespace engine
{
	namespace file_system
	{
		std::string get_current_directory()
		{
			char path[FILENAME_MAX];

			if (_getcwd(path, sizeof(path)))
				return path;

			return empty_string;
		}

		FILE* open_file(const char* path, const char* mode)
		{
			FILE* file = NULL;
			fopen_s(&file, path, mode);

			return file;
		}
	}
}