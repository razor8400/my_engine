#include "common.h"
#include "resources/texture2d.h"
#include "resources/resources_manager.h"
#include "sprite.h"

namespace engine
{
    IMPLEMENT_INHERITANCE_INFO(sprite, game_object);
    
    bool sprite::init()
    {
        if (!game_object::init())
            return false;

        m_shader_program = gl::shaders_manager::instance().get_program(gl::shader_program::shader_texture_position_color);
        
        return true;
    }

    bool sprite::init(const std::string& file_name)
    {
        auto texture = resources_manager::instance().load_resource_from_file<texture2d>(file_name);

        return init(texture);
    }
    
    bool sprite::init(const texture2d_ptr& texture)
    {
        if (!texture || !init())
            return false;
        
        set_texture(texture);
            
        return true;
    }
    
    void sprite::render(const math::mat4& transform)
    {
        if (m_texture)
        {
            m_texture->set_color(math::vector4d(m_color.x, m_color.y, m_color.z, get_alpha()));
            m_texture->draw(transform, m_shader_program);
        }
        
        game_object::render(transform);
    }

    void sprite::set_texture(const std::string& file_name)
    {
        auto texture = resources_manager::instance().load_resource_from_file<texture2d>(file_name);
        
        set_texture(texture);
    }
    
    void sprite::set_texture(const texture2d_ptr& texture)
    {
        m_texture = texture;

        if (m_texture)
        {
            m_size.x = (float)m_texture->get_width();
            m_size.y = (float)m_texture->get_height();
        }
    }
    
    void sprite::set_alpha(float alpha)
    {
        set_opacity(int(alpha * 255));
    }
    
    float sprite::get_alpha() const
    {
        float alpha = get_opacity() / 255.0f;
        
        for (auto parent = get_parent(); parent != nullptr; parent = parent->get_parent())
            alpha *= parent->get_opacity() / 255.0f;
        
        return alpha;
    }
}
