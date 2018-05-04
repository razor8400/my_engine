#pragma once

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <queue>
#include <cstdarg>

#include "gl/libgl.h"
#include "math/libmath.h"

#include "core/type_info.h"

#include "utils/logger.h"
#include "utils/vector.h"
#include "config.h"

namespace engine
{
    class ref;
    class renderer;
    
	class scene;
	class game_object;
    class component;

    class resource;
    class texture2d;
    class script;
    
    class touch_listener;
    
    typedef std::shared_ptr<resource> resource_ptr;
    typedef std::shared_ptr<texture2d> texture2d_ptr;
    typedef std::shared_ptr<script> script_ptr;

	enum projection_mode
	{
		ortographic, perspective
	};
    
    static const std::string empty_string;
    
	static std::string vector3d_to_string(const math::vector3d& v3)
	{
		std::stringstream ss;

		ss << "(" << v3.x << ", "  << v3.y << ", " << v3.z << ")";

		return ss.str();
	}

	static std::string projection_mode_to_string(projection_mode mode)
	{
		if (mode == perspective)
		{
			return "perspective";
		}
		else if (mode == ortographic)
		{
			return "ortographic";
		}

		return empty_string;
	}
}

