#include "common.h"
#include "resources_manager.h"

namespace engine
{
    resources_manager& resources_manager::instance()
    {
        static resources_manager manager;
        
        return manager;
    }
    
    resources_manager::resources_manager()
    {
        
    }
    
    void resources_manager::clear_cache()
    {
        logger() << "[resources_manager] clear cache";
        m_resources.clear();
    }
}
