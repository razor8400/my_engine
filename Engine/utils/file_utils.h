#pragma once

namespace engine
{
	namespace file_utils
	{
        std::string get_resources_folder();
        std::string get_path_to_resource(const std::string& path);
        std::string get_file_name(const std::string& path);
        
        bool file_exist(const std::string& file_name);
        
        bool read_resource_file(const std::string& file_name, unsigned char** data, size_t* size);
        bool read_resource_file(const std::string& file_name, std::vector<char>* buffer);
		bool read_file(const std::string& file_name, unsigned char** data, size_t* size);
        bool read_file(const std::string& file_name, std::vector<char>* buffer);
	};
}
