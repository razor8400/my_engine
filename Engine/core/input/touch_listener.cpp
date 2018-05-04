#include "common.h"
#include "touch_dispatcher.h"
#include "touch_listener.h"

namespace engine
{
    touch_listener::~touch_listener()
    {
        touch_dispatcher::instance().remove_touch_listener(this);
    }
    
    bool touch_listener::on_touch_began()
    {
        if (touch_began)
            return touch_began();
        return false;
    }
    
    void touch_listener::on_touch_moved()
    {
        if (touch_moved)
            touch_moved();
    }
    
    void touch_listener::on_touch_ended()
    {
        if (touch_ended)
            touch_ended();
    }
}
