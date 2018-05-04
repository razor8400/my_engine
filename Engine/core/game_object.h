#pragma once

#include "ref.h"

namespace engine
{
    class game_object : public ref
	{
	public:
        DECLARE_CLASS;
        
        template<class T, class ...Args>
        static T* create(Args... args);
        
		virtual bool init();

		virtual void update(float dt);
		virtual void draw(const math::mat4& world);
        virtual void render(const math::mat4& world);
        
        virtual void on_enter();
        virtual void on_exit();
    public:
        void add_child(game_object* obj);
        void remove_child(game_object* obj);
		void remove_from_parent();
        
        void add_component(component* component);
        void remove_component(component* component);
        
        math::vector3d anchor_point() const { return m_anchor * m_size; }
        math::vector3d global_to_local(const math::vector3d& v3) const;
        math::vector3d local_to_global(const math::vector3d& v3) const;
		
        const math::mat4& get_transform() const { return m_transform; }
    private:
        void mark_dirty() { m_update_transform = true; }
        
        math::mat4 transform(const math::mat4& parent) const;
        
        math::mat4 parent_transform() const;
        math::mat4 world_transform() const;
    public:
        void set_enabled(bool enabled) { m_enabled = enabled; }
        bool get_enabled() const { return m_enabled; }
        
		void set_position(const math::vector3d& position) { m_position = position; mark_dirty(); }
		const math::vector3d& get_position() const { return m_position; }

		void set_rotation(const math::vector3d& rotation) { m_rotation = rotation; mark_dirty(); }
		const math::vector3d& get_rotation() const { return m_rotation; }

		void set_scale(const math::vector3d& scale) { m_scale = scale; mark_dirty(); }
		const math::vector3d& get_scale() const { return m_scale; }

		void set_size(const math::vector3d& size) { m_size = size; mark_dirty(); }
		const math::vector3d& get_size() const { return m_size; }

		void set_anchor(const math::vector3d& anchor) { m_anchor = anchor; mark_dirty(); }
		const math::vector3d& get_anchor() const { return m_anchor; }

		void set_tag(int tag) { m_tag = tag; }
		int get_tag() const { return m_tag; }
        
        void set_opacity(int opacity) { m_opacity = opacity; }
        int get_opacity() const { return m_opacity; }
                
        int get_children_count() const { return (int)m_children.size(); }
        
        game_object* get_parent() const { return m_parent; };
        
        void set_shader_program(const gl::shader_program_ptr& shader_program) { m_shader_program = shader_program; }
        const gl::shader_program_ptr& get_shader_program() const { return m_shader_program; }
	protected:
        engine::vector<game_object*> m_children;
        engine::vector<component*> m_components;
        
		math::vector3d m_position;
		math::vector3d m_rotation;
		math::vector3d m_scale;
		math::vector3d m_size;
        math::vector3d m_anchor;

		math::mat4 m_transform;

		int m_tag = 0;
        int m_opacity = 255;
        
        bool m_active = false;
        bool m_enabled = true;
		bool m_update_transform = false;

		game_object* m_parent = nullptr;
        gl::shader_program_ptr m_shader_program;
	};
    
    template<class T, class ...Args>
    T* game_object::create(Args... args)
    {
        auto obj = ref::create<T>();
        
        if (obj->init(args...))
            return obj;
        
        return nullptr;
    }
}
