#include "common.h"
#include "box_collider2d.h"
#include "core/game_object.h"
#include "core/director.h"

namespace engine
{
    IMPLEMENT_TYPE_INFO(box_collider2d)
    
    box_collider2d::box_collider2d()
    {
        
    }
    
    box_collider2d::box_collider2d(const math::vector2d& size) : m_size(size)
    {
        
    }
    
    bool box_collider2d::on_click(const math::vector2d& location) const
    {
        if (m_vertices.size() > 0)
        {
            std::vector<std::pair<int, int>> indices = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 } };
            
            for (auto it : indices)
            {
                auto p1 = m_vertices[it.first];
                auto p2 = m_vertices[it.second];
                
                auto f = math::line_equation(p1, p2, location);
            
                if (f > 0)
                    return false;
            }
            
            return true;
        }
        
        return false;
    }

    void box_collider2d::update(float dt)
    {
        update();
    }
    
    void box_collider2d::update()
    {
        if (!m_parent || !m_parent->get_enabled())
            return;
        
        auto transform = m_parent->get_transform();
        
        auto p1 = math::transform_point(math::vector2d::zero, transform);
        auto p2 = math::transform_point(math::vector2d(m_size.x, 0), transform);
        auto p3 = math::transform_point(m_size, transform);
        auto p4 = math::transform_point(math::vector2d(0, m_size.y), transform);
        
        m_vertices.clear();
        m_vertices.push_back(p1);
        m_vertices.push_back(p2);
        m_vertices.push_back(p3);
        m_vertices.push_back(p4);
    }
}
