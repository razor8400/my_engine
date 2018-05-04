#include "rect.h"
#include "vector4d.h"

#include <algorithm>

namespace math
{
	rect::rect(float x, float y, float w, float h) : m_origin(x, y), m_size(w, h)
	{

	}

	rect::rect(const vector2d& origin, const vector2d& size) : m_origin(origin), m_size(size)
	{

	}

	bool rect::contains(const vector2d& location) const
	{
		auto bl = bottom_left();
		auto tr = top_right();

		return location.x >= bl.x && location.x <= tr.x && location.y >= bl.y && location.y <= tr.y;
	}

	vector2d rect::bottom_left() const
	{
		return m_origin;
	}

	vector2d rect::top_left() const
	{
		return m_origin + vector2d(0, m_size.y);
	}

	vector2d rect::top_right() const
	{
		return m_origin + m_size;
	}

	vector2d rect::bottom_right() const
	{
		return m_origin + vector2d(m_size.x, 0);
	}

	vector2d rect::center() const
	{
		return bottom_left() + top_right() / 2;
	}

	rect rect::operator*(const mat4& m4) const
	{
		auto bl = bottom_left();
		auto br = bottom_right();

		auto tl = top_left();
		auto tr = top_right();

		auto p1 = vector4d(bl.x, bl.y, 0, 1) * m4;
		auto p2 = vector4d(br.x, br.y, 0, 1) * m4;
		auto p3 = vector4d(tl.x, tl.y, 0, 1) * m4;
		auto p4 = vector4d(tr.x, tr.y, 0, 1) * m4;

        auto min_x = std::min(std::min(p1.x, p2.x), std::min(p3.x, p4.x));
        auto max_x = std::max(std::max(p1.x, p2.x), std::max(p3.x, p4.x));
        auto min_y = std::min(std::min(p1.y, p2.y), std::min(p3.y, p4.y));
        auto max_y = std::max(std::max(p1.y, p2.y), std::max(p3.y, p4.y));
        
		return rect(min_x, min_y, max_x - min_x, max_y - min_y);
	}

	rect rect::operator*(const float s) const
	{
		return rect(m_origin * s, m_size * s);
	}

	rect rect::operator*(const vector2d& s) const
	{
		return rect(m_origin * s, m_size * s);
	}
}

