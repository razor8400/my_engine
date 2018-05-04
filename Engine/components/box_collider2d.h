#pragma once

#include "component.h"

namespace engine
{
    class box_collider2d : public component
    {
        DECLARE_CLASS;
    public:
        box_collider2d();
        box_collider2d(const math::vector2d& size);
        
        bool on_click(const math::vector2d& location) const;
        
        void set_size(const math::vector2d& size) { m_size = size; }
        const math::vector2d& get_size() const { return m_size; }
        
        void start() override {};
        void update(float dt) override;
        void stop() override {};
    private:
        void update();
    private:
        math::vector2d m_size;
        std::vector<math::vector2d> m_vertices;
    };
}
