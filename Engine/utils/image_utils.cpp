#include "common.h"

#include "platform/file_system/file_system.h"

#include "image_utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace engine
{
    namespace image_utils
    {
        int stbi_format_to_gl(int format)
        {
            static std::map<int, int> formats =
            {
                { STBI_grey, GL_RGB },
                { STBI_grey_alpha, GL_RGBA },
                { STBI_rgb, GL_RGB },
                { STBI_rgb_alpha, GL_RGBA },
            };
            
            auto it = formats.find(format);
            
            if (it != formats.end())
                return it->second;
            
            return -1;
        }
        
        bool load_image_from_file(const std::string& file_name, image_data* data)
        {
            auto file = file_system::open_file(file_name.c_str(), "rb");
            
            if (file)
            {
                data->buffer = stbi_load_from_file(file, &data->width, &data->height, &data->format, STBI_rgb_alpha);
                data->format = stbi_format_to_gl(data->format);
                
                fclose(file);
                
                return true;
            }
            
            data->error = "can't open file:" + file_name;
            return false;
        }
        
        std::string get_image_format(const std::string& file_name)
        {
            auto i = file_name.find_last_of('.');
            
            if (i != std::string::npos)
                return file_name.substr(i + 1);
            
            return format::unknown;
        }
    }
}
