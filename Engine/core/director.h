#pragma once

#include "common.h"

namespace engine
{
	class renderer;
    
    class director
    {
    public:
        static director& instance();
        
        math::vector3d convert_screen_to_world(const math::vector2d& screen) const;
        
		void set_projection_mode(projection_mode mode);
		
		void set_near_plane(float near_plane);
		void set_far_plane(float far_plane);
		void set_field_of_view(float field_of_view);

		void set_camera_position(const math::vector3d& position);

		void start();
        void stop();
				
        void run_scene(scene* scene);
        
		void main_loop();
        
        scene* running_scene() const { return m_scene; }
        float get_delta_time() const;
        time_t get_local_time() const;
	private:
        void update(float delta_time);
        
        director();
        ~director();
    private:
        scene* m_scene = nullptr;
        scene* m_next_scene = nullptr;

		bool m_running = false;

		std::unique_ptr<renderer> m_renderer;
    };
}
