#pragma once

#include "resources_manager.h"
#include "utils/file_utils.h"

#include "texture2d.h"
#include "script.h"

namespace engine
{
    template<class T>
    std::shared_ptr<T> resources_manager::load_resource_from_file(const std::string& file_name) const
    {
        auto path = file_utils::get_path_to_resource(file_name);
        auto it = m_resources.find(path);
        
		if (it != m_resources.end())
			return std::dynamic_pointer_cast<T>(it->second);
		        
		logger() << "[resources] load resource from file:" << path;
        auto resource = T::load_from_file(path);
        
        if (resource)
            m_resources[path] = resource;
        
        return resource;
    }
}
