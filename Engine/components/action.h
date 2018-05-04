#pragma once

#include "component.h"

struct lua_State;

namespace engine
{
    class action : public component
    {
        DECLARE_CLASS
    public:
        virtual void stop() {};
        virtual bool is_action_done() const = 0;
    protected:
        virtual void done_action();
    };
    
    class targeted_action : public action
    {
        DECLARE_CLASS
    public:
        static targeted_action* create(action* action, game_object* target);
        
        void start() override;
        void update(float dt) override;
        
        bool is_action_done() const override { return m_action->is_action_done(); }
    private:
        action* m_action = nullptr;
        game_object* m_target = nullptr;
    };
    
    class action_instant : public action
    {
        DECLARE_CLASS
    public:
        void start() override;
        void update(float dt) override;
        
        bool is_action_done() const override { return m_handled; }
    protected:
        virtual void handle_action() = 0;
    private:
        bool m_handled = false;
    };
    
    class action_lua_callback : public action_instant
    {
        DECLARE_CLASS
    public:
        static action_lua_callback* create(lua_State* state, int handler);
        void handle_action() override;
    private:
        lua_State* m_state;
        int m_handler;
    };
    
    class action_inverval : public action
    {
        DECLARE_CLASS
    public:
        virtual void start() override;
        virtual void update(float dt) override;
        
        float get_duration() const { return m_duration; }
        bool is_action_done() const override { return m_time >= m_duration; }
    protected:
        virtual void step(float s) = 0;
    protected:
        float m_time = 0;
        float m_duration = 0;
    };
    
    class action_sequence : public action
    {
        DECLARE_CLASS
    public:
        static action_sequence* sequence(const vector<action*>& actions);
        
        void append(action* action);
        void update(float dt) override;
        
        bool is_action_done() const override { return m_current_action >= m_actions.size(); }
    private:
        void start() override;
        void start_next_action();
    private:
        vector<action*> m_actions;
        size_t m_current_action = 0;
    };
    
    class action_list : public action
    {
        DECLARE_CLASS
    public:
        static action_list* list(const vector<action*>& actions);
        
        void append(action* action);
        void update(float dt) override;
        
        bool is_action_done() const override { return m_counter >= m_actions.size(); }
    private:
        void start() override;
    private:
        vector<action*> m_actions;
        size_t m_counter = 0;
    };
    
    class action_delay : public action_inverval
    {
        DECLARE_CLASS
    public:
        static action_delay* delay(float duration);
    private:
        void step(float s) {};
    };
    
    class action_move : public action_inverval
    {
        DECLARE_CLASS
    public:
        static action_move* move(const math::vector3d& from, const math::vector3d& to, float duration);
        static action_move* move_to(const math::vector3d& to, float duration);
        static action_move* move_by(const math::vector3d& by, float duration);
    protected:
        void step(float s) override;
        void start() override;
    protected:
        math::vector3d m_from;
        math::vector3d m_to;
        math::vector3d m_by;
        
        bool m_move_by = false;
        bool m_use_target_location = false;
    };
}
