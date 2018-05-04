#pragma once

namespace engine
{
    class touch_listener;
    
    class touch_dispatcher
    {
    public:
        static touch_dispatcher& instance();
        
        void on_touch_began();
        void on_touch_moved();
        void on_touch_ended();
        
        void add_touch_listener(touch_listener* listener);
        void remove_touch_listener(touch_listener* listener);
    private:
        touch_dispatcher();
        ~touch_dispatcher();
    private:
        vector<touch_listener*> m_listeners;
        vector<touch_listener*> m_active_listeners;
    };
}
