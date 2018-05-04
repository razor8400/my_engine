#include "common.h"
#include "ref.h"
#include "pool_manager.h"

namespace engine
{
    pool_manager& pool_manager::instance()
    {
        static pool_manager manager;
        
        return manager;
    }
    
    pool_manager::pool_manager()
    {
        
    }
    
    pool_manager::~pool_manager()
    {
        
    }
    
    void pool_manager::push(ref* obj)
    {
        m_pool.push_back(obj);
    }
    
    void pool_manager::update()
    {
        m_pool.lock([this]()
        {
            for (auto obj : m_pool)
            {
                if (obj->counter() > 1)
                    continue;
                
                m_pool.erase(obj);
            }
        });
    }
}
