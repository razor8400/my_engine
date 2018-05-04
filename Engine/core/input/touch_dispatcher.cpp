#include "common.h"
#include "touch_dispatcher.h"
#include "touch_listener.h"

namespace engine
{
    touch_dispatcher& touch_dispatcher::instance()
    {
        static touch_dispatcher instance;
        return instance;
    }
    
    touch_dispatcher::touch_dispatcher()
    {
        
    }
    
    touch_dispatcher::~touch_dispatcher()
    {
        
    }
    
    void touch_dispatcher::add_touch_listener(touch_listener* listener)
    {
        m_listeners.push_back(listener);
        std::sort(m_listeners.begin(), m_listeners.end(), [](touch_listener* a, touch_listener* b)
        {
            return a->priority < b->priority;
        });
    }
    
    void touch_dispatcher::remove_touch_listener(touch_listener* listener)
    {
        m_listeners.erase(listener);
    }
    
    void touch_dispatcher::on_touch_began()
    {
        for (auto listener : m_listeners)
        {
            if (listener->on_touch_began())
            {
                m_active_listeners.push_back(listener);
                
                if (!listener->swallow_touches)
                    break;
            }
        }
    }
    
    void touch_dispatcher::on_touch_moved()
    {
        for (auto listener : m_active_listeners)
            listener->on_touch_moved();
    }
    
    void touch_dispatcher::on_touch_ended()
    {
        for (auto listener : m_active_listeners)
            listener->on_touch_ended();
        
        m_active_listeners.clear();
    }
}
