#include "common.h"
#include "application.h"
#include "platform/platform.h"
#include "interface/app_delegate.h"

namespace engine
{
    application& application::instance()
    {
        static application instance;
        return instance;
    }
    
	void application::set_win_size(int width, int height)
	{
		m_win_size.x = (float)width;
		m_win_size.y = (float)height;
	}

	void application::set_display_name(const std::string& display_name)
	{
		m_display_name = display_name;
	}

	void application::set_delegate(app_delegate* delegate)
	{
		m_delegate = delegate;
	}

	void application::on_launched()
	{
		logger() << "[application] application launched";
		logger() << "[application] platform:" << platform::instance().get_platform_code();

		if (m_delegate)
			m_delegate->application_launched(this);
	}
    
    void application::on_terminated()
    {
        logger() << "[application] application terminated";
        
        if (m_delegate)
            m_delegate->application_terminated(this);
    }
    
    void application::on_enter_background()
    {
        logger() << "[application] application enter background";
        
        if (m_delegate)
            m_delegate->application_enter_background(this);
    }
    
    void application::on_enter_foreground()
    {
        logger() << "[application] application enter foreground";
        
        if (m_delegate)
            m_delegate->application_enter_foreground(this);
    }
    
    bool application::create_context_window()
    {
        m_window = std::make_unique<window>();
        
		if (!m_window->create(m_display_name.c_str(), (int)m_win_size.x, (int)m_win_size.y))
		{
			logger() << "[application] failed to create application window";
			return false;
		}
        
		if (!gl::init_gl())
		{
			logger() << "[application] open gl init failed";
			return false;
		}

		logger() << "[application] create context window";
		logger() << "[application] title:" << m_display_name;
		logger() << "[application] width:" << (int)m_win_size.x;
		logger() << "[application] height:" << (int)m_win_size.y;
		        
        gl::compile_shaders();
        gl::generate_buffers();
        
        return true;
    }

	void application::run()
	{   
		logger() << "[application] run";

        if (m_window)
            m_window->process();
	}
    
    void application::shutdown()
    {
        logger() << "[application] shutdown";
        
        gl::clear_buffers();
    }
    
    math::vector2d application::get_mouse_location() const
    {
        if (m_window)
            return m_window->get_mouse_location();
        return math::vector2d::zero;
    }
}

