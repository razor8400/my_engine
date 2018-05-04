#pragma once

#include <vector>
#include <memory>
#include <map>

#include "GLEW/glew.h"
#include "math/libmath.h"

namespace gl
{
    bool init_gl();

    void enable_depth();
	void generate_buffers();
    void clear_buffers();
    void compile_shaders();
    void clear();
    
    GLint create_gl_program(const char* vert, const char* frag);
	GLuint load_texture(const unsigned char* data, int width, int height, GLuint format);
    
    void bind_texture(GLuint texture);
    void set_blend_func(GLenum source, GLenum destination);
    void draw_texture2d(float x, float y, float width, float height);
    void delete_texture(GLuint texture);
    
    void draw_line(float x1, float y1, float x2, float y2);
    void draw_rect(float x, float y, float width, float height);
    
    struct blend_func
    {
        GLenum source;
        GLenum destination;
    };
}
