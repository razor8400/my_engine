#pragma once

#include <stdio.h>

namespace engine
{
    namespace file_system
    {
        std::string get_current_directory();
		FILE* open_file(const char* path, const char* mode);
    }
}
