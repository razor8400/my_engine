#include "common.h"
#include "action.h"

#include "scripting/scripting.h"
#include "core/game_object.h"

namespace engine
{
    IMPLEMENT_TYPE_INFO(action)
    
    void action::done_action()
    {
        m_parent->remove_component(this);
    }
    
    IMPLEMENT_TYPE_INFO(targeted_action)
    
    targeted_action* targeted_action::create(action* act, game_object* target)
    {
        auto action = ref::create<targeted_action>();
        
        action->m_action = act;
        action->m_target = target;
        
        return action;
    }
    
    void targeted_action::start()
    {
        m_target->add_component(m_action);
    }
    
    void targeted_action::update(float dt)
    {
        if (is_action_done())
            done_action();
    }
    
    IMPLEMENT_TYPE_INFO(action_instant)
    
    void action_instant::start()
    {
        handle_action();
        m_handled = true;
    }
    
    void action_instant::update(float dt)
    {
        if (is_action_done())
            done_action();
    }
    
    IMPLEMENT_TYPE_INFO(action_lua_callback)
    
    action_lua_callback* action_lua_callback::create(lua_State* state, int handler)
    {
        auto action = ref::create<action_lua_callback>();
        
        action->m_handler = handler;
        action->m_state = state;
        
        return action;
    }
    
    void action_lua_callback::handle_action()
    {
        scripting::call_method(m_state, m_handler);
    }
    
    void action_inverval::start()
    {
        m_time = 0;
    }
    
    void action_inverval::update(float dt)
    {
        if (m_duration > 0)
        {
            m_time += dt;
            step(std::max(0.0f, std::min(m_time / m_duration, 1.0f)));
        }
        
        if (is_action_done())
            done_action();
    }
    
    IMPLEMENT_TYPE_INFO(action_sequence)
    
    action_sequence* action_sequence::sequence(const vector<action*>& actions)
    {
        auto action = ref::create<action_sequence>();
        action->m_actions = actions;
        
        return action;
    }
    
    void action_sequence::append(action* action)
    {
        m_actions.push_back(action);
    }
    
    void action_sequence::start()
    {
        m_current_action = 0;
        start_next_action();
    }
    
    void action_sequence::update(float dt)
    {
        if (is_action_done())
        {
            done_action();
        }
        else
        {
            auto action = m_actions.at(m_current_action);
            if (action->is_action_done())
            {
                ++m_current_action;
                start_next_action();
            }
        }
    }
    
    void action_sequence::start_next_action()
    {
        if (m_current_action < m_actions.size())
        {
            auto action = m_actions.at(m_current_action);
            m_parent->add_component(action);
        }
    }
    
    IMPLEMENT_TYPE_INFO(action_list)
    
    action_list* action_list::list(const vector<action*>& actions)
    {
        auto action = ref::create<action_list>();
        
        action->m_actions = actions;
        
        return action;
    }
    
    void action_list::append(action* action)
    {
        m_actions.push_back(action);
    }
    
    void action_list::update(float dt)
    {
        for (auto action : m_actions)
        {
            if (action->is_action_done())
                ++m_counter;
        }
    }
    
    void action_list::start()
    {
        for (auto action : m_actions)
            m_parent->add_component(action);
    }
    
    IMPLEMENT_TYPE_INFO(action_delay)
    
    action_delay* action_delay::delay(float duration)
    {
        auto action = ref::create<action_delay>();
        
        action->m_duration = duration;
        
        return action;
    }
    
    IMPLEMENT_TYPE_INFO(action_move)
    
    action_move* action_move::move(const math::vector3d& from, const math::vector3d& to, float duration)
    {
        auto action = ref::create<action_move>();
        
        action->m_from = from;
        action->m_to = to;
        action->m_duration = duration;
        
        return action;
    }
    
    action_move* action_move::move_to(const math::vector3d& to, float duration)
    {
        auto action = ref::create<action_move>();
        
        action->m_use_target_location = true;
        action->m_to = to;
        action->m_duration = duration;
        
        return action;
    }
    
    action_move* action_move::move_by(const math::vector3d& by, float duration)
    {
        auto action = ref::create<action_move>();
        
        action->m_move_by = true;
        action->m_by = by;
        action->m_duration = duration;
        
        return action;
    }
    
    void action_move::step(float s)
    {
        auto delta = m_to - m_from;

        m_parent->set_position(m_from + (delta * s));
    }
    
    void action_move::start()
    {
        if (m_use_target_location)
        {
            m_from = m_parent->get_position();
        }
        else
        {
            m_parent->set_position(m_from);
        }
        
        if (m_move_by)
            m_to = m_parent->get_position() + m_by;
        
        action_inverval::start();
    }
}
