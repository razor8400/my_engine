#include "common.h"

#include "file_utils.h"
#include "platform/file_system/file_system.h"

namespace engine
{
    namespace file_utils
    {
        static const char* assets_folder = "Assets/";
        
        bool read_resource_file(const std::string& file_name, unsigned char** data, size_t* size)
        {
            auto path = get_path_to_resource(file_name);
            
            if (read_file(path, data, size))
                return true;
            
            logger() << "[file_utils] can't open resource file:" << file_name;
            
            return false;
        }
        
        bool read_resource_file(const std::string& file_name, std::vector<char>* buffer)
        {
            auto path = get_path_to_resource(file_name);
            
            if (read_file(path, buffer))
                return true;
            
            logger() << "[file_utils] can't open resource file:" << file_name;
            
            return false;
        }
        
        bool read_file(const std::string& file_name, std::vector<char>* buffer)
        {
            if (!buffer)
                return false;
            
            unsigned char* data;
            size_t size;
            
            if (read_file(file_name, &data, &size))
            {
                buffer->clear();
                buffer->reserve(size);
                buffer->insert(buffer->end(), data, data + size);
                
                delete [] data;
                
                return true;
            }
            
            return false;
        }
        
        bool read_file(const std::string& file_name, unsigned char** data, size_t* size)
        {
            auto file = file_system::open_file(file_name.c_str(), "rb");
            
            if (file != NULL)
            {
                fseek(file, 0, SEEK_END);
                
                *size = ftell(file);
                *data = new unsigned char[*size];

                fseek(file, 0, 0);
                
                auto bytes_read = fread(*data, sizeof(unsigned char), *size, file);
                
                fclose(file);
                
                return bytes_read == *size;
            }
            
            return false;
        }
        
        std::string get_resources_folder()
        {
            return file_system::get_current_directory() + '/' + assets_folder;
        }
        
        std::string get_path_to_resource(const std::string& path)
        {
            return get_resources_folder() + path;
        }
        
        std::string get_file_name(const std::string& path)
        {
            auto file = path;
            auto i = file.find_last_of('/');
            
            if (i != std::string::npos)
            {
                file = file.substr(i + 1);
                i = file.find_last_of('.');
                
                if (i != std::string::npos)
                    file = file.substr(0, i);
            }
            
            return file;
        }
    }
}
