#pragma once

#include "resource.h"

namespace engine
{        
    class resources_manager
    {
    public:
        static resources_manager& instance();
        
        template<class T>
        std::shared_ptr<T> load_resource_from_file(const std::string& file_name) const;
        
        void clear_cache();
    private:
        resources_manager();
        
        mutable std::map<std::string, resource_ptr> m_resources;
    };
}

#include "resources_manager.inl"

