#pragma once

#include "component.h"

namespace engine
{
    class scriptable_component : public component
    {
        DECLARE_CLASS;
    public:
        static scriptable_component* create(const std::string& file_name);
        
        ~scriptable_component();
        
        void start() override;
        void update(float dt) override;
        void stop() override;
    private:
        script_ptr m_script;
        touch_listener* m_listener = nullptr;
    };
}
