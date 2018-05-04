#include "common.h"

#include <chrono>

#include "director.h"
#include "application.h"

#include "renderer/renderer.h"
#include "resources/resources_manager.h"

#include "scene.h"
#include "pool_manager.h"

namespace engine
{
    director& director::instance()
    {
        static director instance;
        return instance;
    }
    
    director::director()
    {
		m_renderer = std::make_unique<renderer>();
    }
    
    director::~director()
    {

    }
    
    math::vector3d director::convert_screen_to_world(const math::vector2d& screen) const
    {
        auto win_size = application::instance().get_win_size();
        return screen - win_size / 2.0f;
    }
    
	void director::set_projection_mode(projection_mode mode)
	{
		m_renderer->set_projection_mode(mode);
	}

	void director::set_near_plane(float near_plane)
	{
		m_renderer->set_near_plane(near_plane);
	}

	void director::set_far_plane(float far_plane)
	{
		m_renderer->set_far_plane(far_plane);
	}

	void director::set_field_of_view(float field_of_view)
	{
		m_renderer->set_field_of_view(field_of_view);
	}

	void director::set_camera_position(const math::vector3d& position)
	{
		m_renderer->set_camera_position(position);
	}

	void director::start()
    {
		logger() << "[director] start";
		m_renderer->dump_camera_settings();
        m_running = true;
    }
    
    void director::stop()
    {
        m_running = false;
    }
    
    void director::run_scene(scene* scene)
    {
		logger() << "[director] run scene";
        
        m_next_scene = scene;
    }
    
    void director::main_loop()
    {
        if (m_next_scene)
        {
            if (m_scene)
            {
                m_scene->on_exit();
                m_scene->release();
            }
            
            m_scene = m_next_scene;
            m_scene->retain();
            m_scene->on_enter();
            
            m_next_scene = nullptr;
        }
        
        if (m_running)
        {
            auto delta = get_delta_time();
            
            update(delta);
        }
    }
    
    void director::update(float delta_time)
    {
        if (m_scene)
        {
            m_scene->update(delta_time);
			m_renderer->draw_scene(m_scene);
        }
        
		pool_manager::instance().update();
    }
    
    float director::get_delta_time() const
    {
        static auto last_update = std::chrono::steady_clock::now();
        
        auto now = std::chrono::steady_clock::now();
        auto delta = std::chrono::duration_cast<std::chrono::duration<float>>(now - last_update);
        
        last_update = now;
        
        return delta.count();
    }
    
    time_t director::get_local_time() const
    {
        auto now = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

        return ms.count();
    }
}
