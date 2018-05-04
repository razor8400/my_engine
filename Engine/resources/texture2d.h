#pragma once

#include "resource.h"

namespace engine
{
    class texture2d : public resource
	{
    public:
        static std::shared_ptr<texture2d> load_from_file(const std::string& file_name);
        
        texture2d(int width, int height, int format);
        virtual ~texture2d();
        
        bool load(const unsigned char* data, size_t size) override;
        void draw(const math::mat4& transform, const gl::shader_program_ptr& shader_program);
        
        int get_width() const { return m_width; }
        int get_height() const { return m_height; }
        
        void set_color(const math::vector4d& color) { m_color = color; }
        const math::vector4d& get_color() const { return m_color; }
    private:
		int m_width = 0;
		int m_height = 0;
        int m_format = 0;
        int m_texture_id = -1;
        
        math::vector4d m_color = math::vector4d::one;
        gl::blend_func m_blend_func = { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA };
	};
}
