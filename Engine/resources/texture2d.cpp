#include "common.h"
#include "utils/image_utils.h"
#include "texture2d.h"

namespace engine
{
    static const int texture_default_id = -1;
    
    std::shared_ptr<texture2d> texture2d::load_from_file(const std::string& file_name)
    {
        auto data = image_utils::image_data();

		logger() << "[texture2d] load:" << file_name;
        
        if (image_utils::load_image_from_file(file_name, &data))
        {
            auto texture = std::make_shared<texture2d>(data.width, data.height, data.format);
            
            if (texture->load(data.buffer, 0))
                return texture;
        }
        
		logger() << "[texture2d] load error:" << data.error;
        
        return std::shared_ptr<texture2d>();
    }
    
    texture2d::texture2d(int width, int height, int format) : m_width(width), m_height(height), m_format(format)
    {
        
    }
    
    texture2d::~texture2d()
    {
        if (m_texture_id != texture_default_id)
            gl::delete_texture(m_texture_id);
    }
    
    bool texture2d::load(const unsigned char* data, size_t size)
    {
        m_texture_id = gl::load_texture(data, m_width, m_height, m_format);
        
        return m_texture_id != texture_default_id;
    }
    
    void texture2d::draw(const math::mat4& transform, const gl::shader_program_ptr& shader_program)
    {
        gl::bind_texture(m_texture_id);
        gl::set_blend_func(m_blend_func.source, m_blend_func.destination);
        
        if (shader_program)
            shader_program->use(transform, m_color);
        
        gl::draw_texture2d(0, 0, (float)m_width, (float)m_height);
    }
}
