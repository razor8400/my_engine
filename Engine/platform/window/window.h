#pragma once

namespace engine
{
    class window
    {
    public:
        window();
		bool create(const char* display_name, int width, int height);
		void process();
        void terminate();
        const math::vector2d& get_win_size() const { return m_size; }
        math::vector2d get_mouse_location() const;
    private:
		math::vector2d m_size;
    };
}
