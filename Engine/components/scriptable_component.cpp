#include "common.h"
#include "scriptable_component.h"

#include "resources/script.h"
#include "resources/resources_manager.h"

#include "core/input/touch_listener.h"
#include "core/input/touch_dispatcher.h"

namespace engine
{
    IMPLEMENT_TYPE_INFO(component)
    
    scriptable_component* scriptable_component::create(const std::string& file_name)
    {
        auto resource = resources_manager::instance().load_resource_from_file<script>(file_name);
        
        if (resource)
        {
            auto component = ref::create<scriptable_component>();
            component->m_script = resource;
            return component;
        }
        
        return nullptr;
    }
    
    scriptable_component::~scriptable_component()
    {

    }
    
    void scriptable_component::start()
    {
        if (m_script)
        {
			if (!m_script->run())
			{
				m_script.reset();
				return;
			}
            
            m_listener = ref::create<touch_listener>();
            m_listener->touch_began = [=]()
            {
                return m_script->call_boolean_function(scripting::on_touch_began);
            };
            
            m_listener->touch_moved = [=]()
            {
                m_script->call_function(scripting::on_touch_moved);
            };
            
            m_listener->touch_ended = [=]()
            {
                m_script->call_function(scripting::on_touch_ended);
            };

            m_script->push_user_data("obj", m_parent);
            m_script->call_function(scripting::start);
            
            touch_dispatcher::instance().add_touch_listener(m_listener);
        }
    }
    
    void scriptable_component::update(float dt)
    {
        if (m_script)
            m_script->call_function(scripting::update);
    }
    
    void scriptable_component::stop()
    {
        if (m_script)
        {
            m_script->call_function(scripting::stop);
            m_script->stop();
            
            if (m_listener)
            {
                touch_dispatcher::instance().remove_touch_listener(m_listener);
                m_listener = nullptr;
            }
        }
    }
}
