#pragma once

#include "platform/window/window.h"

namespace engine
{
	class app_delegate;

	class application
	{
	public:
        static application& instance();
        
		void set_win_size(int width, int height);
		void set_display_name(const std::string& display_name);
		void set_delegate(app_delegate* delegate);

		void on_launched();
        void on_terminated();
        void on_enter_background();
        void on_enter_foreground();
        
        bool create_context_window();
		void run();
        void shutdown();
        const math::vector2d& get_win_size() const { return m_win_size; }
        math::vector2d get_mouse_location() const;
	private:
        application() {};
        
		std::string m_display_name;
        math::vector2d m_win_size;

		app_delegate* m_delegate = nullptr;
		std::unique_ptr<window> m_window;
	};
}
