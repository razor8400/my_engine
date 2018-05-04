#include "common.h"

#include "core/director.h"
#include "core/application.h"
#include "core/input/touch_dispatcher.h"

#include "platform/window/window.h"

#include "GLFW3/glfw3.h"

namespace engine
{   
    GLFWwindow* g_window = nullptr;
    
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
            if (action == GLFW_PRESS)
            {
                touch_dispatcher::instance().on_touch_began();
            }
            else if (action == GLFW_RELEASE)
            {
                touch_dispatcher::instance().on_touch_ended();
            }
		}
	}

	void mouse_move_callback(GLFWwindow* window, double x, double y)
	{
        touch_dispatcher::instance().on_touch_moved();
	}

    void window_close_callback(GLFWwindow* window)
    {
        application::instance().on_terminated();
    }
    
    void window_iconify_callback(GLFWwindow* window, int iconified)
    {
        if (iconified)
        {
            application::instance().on_enter_background();
        }
        else
        {
            application::instance().on_enter_foreground();
        }
    }
    
	window::window()
	{

	}

	bool window::create(const char* display_name, int width, int height)
	{
		if (!glfwInit())
			return false;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		g_window = glfwCreateWindow(width, height, display_name, NULL, NULL);
		m_size.x = (float)width;
		m_size.y = (float)height;
		
		if (!g_window)
		{
			glfwTerminate();
			return false;
		}
        
        glfwMakeContextCurrent(g_window);
        
		glfwSetCursorPosCallback(g_window, mouse_move_callback);
		glfwSetMouseButtonCallback(g_window, mouse_button_callback);
        
        glfwSetWindowCloseCallback(g_window, window_close_callback);
        glfwSetWindowIconifyCallback(g_window, window_iconify_callback);

		return true;
	}

	void window::process()
    {
		while (!glfwWindowShouldClose(g_window))
        {           
			director::instance().main_loop();
            
            glfwSwapBuffers(g_window);
            glfwPollEvents();
        }
        
        terminate();
    }
    
    void window::terminate()
    {
        glfwTerminate();
    }
    
    math::vector2d window::get_mouse_location() const
    {
        double x, y;
        glfwGetCursorPos(g_window, &x, &y);
        
        y = m_size.y - y;
        
        return math::vector2d((float)x, (float)y);
    }
}
