#include "common.h"
#include "renderer.h"

#include "core/application.h"
#include "core/scene.h"

namespace engine
{
	void renderer::set_projection_mode(projection_mode mode)
	{
		m_projection_mode = mode;
		update_world();
	}

	void renderer::set_near_plane(float near_plane)
	{
		m_near_plane = near_plane;
		update_world();
	}

	void renderer::set_far_plane(float far_plane)
	{
		m_far_plane = far_plane;
		update_world();
	}

	void renderer::set_field_of_view(float field_of_view)
	{
		m_field_of_view = field_of_view;
		update_world();
	}

	void renderer::set_camera_position(const math::vector3d& position)
	{
		m_camera_position = position;
		update_world();
	}

	void renderer::draw_scene(scene* scene)
	{
		if (scene)
		{
			gl::clear();

			scene->draw(m_world);
		}
	}

	void renderer::dump_camera_settings()
	{
		logger() << "[camera] "
			<< "mode:" << projection_mode_to_string(m_projection_mode) << ", "
			<< "position:" << vector3d_to_string(m_camera_position) << ", "
			<< "field of view:" << m_field_of_view << ", "
			<< "far plane:" << m_far_plane << ", "
			<< "near plane:" << m_near_plane;
	}

	void renderer::update_world()
	{
		auto win_size = application::instance().get_win_size();

		auto camera = math::mat4::look_at(m_camera_position, math::vector3d::zero, math::vector3d::up);

		if (m_projection_mode == perspective)
		{
			m_world = math::mat4::perspective(m_field_of_view, win_size.x / win_size.y, m_near_plane, m_far_plane) * camera;
		}
		else if (m_projection_mode == ortographic)
		{
			m_world = math::mat4::ortographic(win_size.x, win_size.y, m_near_plane, m_far_plane) * camera;
		}
	}
}
