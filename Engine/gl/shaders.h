#pragma once

namespace gl
{
    namespace shaders
    {
        static const char* shader_color = R"(#version 330 core
                                            out vec3 color;
                                            void main()
                                            {
                                                color = vec3(1, 1, 1);
                                            })";

        static const char* shader_position = R"(#version 330 core
                                            layout(location = 0) in vec3 vertex_position_modelspace;
                                            uniform mat4 mvp;
                                            void main()
                                            {
                                                gl_Position = mvp * vec4(vertex_position_modelspace, 1);
                                            })";

		static const char* shader_texture_color = R"(#version 330 core
												in vec2 uv;
												out vec4 color;
                                                uniform vec4 tint;
												uniform sampler2D sampler2d;
												void main()
												{
                                                    color = texture(sampler2d, uv).rgba * tint;
												})";

		static const char* shader_texture_position = R"(#version 330 core
													layout(location = 0) in vec3 vertex_position_modelspace;
													layout(location = 1) in vec2 vertex_uv;
													out vec2 uv;
													uniform mat4 mvp;
													void main()
													{
													   gl_Position = mvp * vec4(vertex_position_modelspace, 1);
													   uv = vertex_uv;
													})";
        
        static const char* mvp = "mvp";
        static const char* texture_sampler2d = "sampler2d";
        static const char* tint = "tint";
    }
}
