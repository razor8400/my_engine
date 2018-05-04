#pragma once

#include "core/game_object.h"

namespace engine
{    
    class sprite : public game_object
    {
        DECLARE_CLASS;
    public:
        bool init() override;
        bool init(const std::string& file_name);
        bool init(const texture2d_ptr& texture);
        void render(const math::mat4& world) override;

        void set_texture(const std::string& file_name);
        void set_texture(const texture2d_ptr& texture);

        void set_color(const math::vector3d& color) { m_color = color; }
        const math::vector3d& get_color() const { return m_color; }
        
        void set_alpha(float alpha);
        float get_alpha() const;
    private:
        texture2d_ptr m_texture;
        math::vector3d m_color = math::vector3d::one;
    };
}
