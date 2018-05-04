#include "common.h"
#include "pool_manager.h"
#include "ref.h"

namespace engine
{
    ref::ref()
    {

    }
    
    ref::~ref()
    {
        
    }
    
    ref* ref::retain()
    {
        ++m_counter;
        return this;
    }
    
    ref* ref::autorelease()
    {
        pool_manager::instance().push(this);
        return this;
    }
    
    void ref::release()
    {
        --m_counter;
        if (m_counter == 0)
            delete this;
    }
}
