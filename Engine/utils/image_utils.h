#pragma once

namespace engine
{
    namespace format
    {
        static const char* png = "png";
        static const char* jpeg = "jpg";
        static const char* pvr4 = "pvr4";
        static const char* unknown = "unknown";
    }
    
    namespace image_utils
    {
		struct image_data
		{
			int width;
			int height;
			int format;
            int bit_depth;
            
            unsigned char* buffer;
            
            std::string error;
		};
    
        bool load_image_from_file(const std::string& file_name, image_data* data);
        std::string get_image_format(const std::string& file_name);
    }
}
