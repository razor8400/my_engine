#include <stdio.h>
#include <unistd.h>

#include "file_system.h"

namespace engine
{
    namespace file_system
    {
        std::string get_current_directory()
        {
            char path[FILENAME_MAX];
            
            if (getcwd(path, sizeof(path)))
                return path;
            
            return empty_string;
        }
        
        FILE* open_file(const char* path, const char* mode)
        {
            return fopen(path, mode);
        }
    }
}
