#include "gl.h"
#include "shaders_manager.h"

namespace gl
{
    static GLuint vertex_array;
    static GLuint current_texture = -1;
    
    namespace vertex_attribute
    {
        static const int position = 0;
        static const int texture_position = 1;
        static const int color = 2;
    };
    
    namespace buffers
    {
        static GLuint position;
        static GLuint color;
        static GLuint texture_position;
    };
    
    bool init_gl()
    {
        glewExperimental = true;
        
        if (glewInit() != GLEW_OK)
            return false;
        
        return true;
    }
    
    void enable_depth()
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

	void generate_buffers()
	{
		glGenVertexArrays(1, &vertex_array);
		glBindVertexArray(vertex_array);
        
        glGenBuffers(1, &buffers::position);
        glGenBuffers(1, &buffers::texture_position);
        glGenBuffers(1, &buffers::color);
    }
    
	void clear_buffers()
	{
		glDeleteVertexArrays(1, &vertex_array);
        
        glDeleteBuffers(1, &buffers::position);
        glDeleteBuffers(1, &buffers::texture_position);
        glDeleteBuffers(1, &buffers::color);
	}

	void compile_shaders()
    {
        auto& manager = shaders_manager::instance();
        manager.compile_default_shaders();
    }

    void clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    GLint compile_shader(const char* source, unsigned int shader)
    {
        GLint result = GL_FALSE;
        int info_log_length = -1;
        
        GLuint shader_id = glCreateShader(shader);
        
        glShaderSource(shader_id, 1, &source , NULL);
        glCompileShader(shader_id);
        
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
        
        if (info_log_length > 0)
        {
            char* error_message = new char[info_log_length + 1];
            glGetShaderInfoLog(shader_id, info_log_length, NULL, error_message);
            fprintf(stdout, "%s", error_message);
            delete[] error_message;
        }
        
        return shader_id;
    }
    
    GLint create_gl_program(const char* vert, const char* frag)
    {
        GLint result = GL_FALSE;
        int info_log_length = -1;
        
        GLuint vertex_shader = compile_shader(vert, GL_VERTEX_SHADER);
        GLuint fragment_shader = compile_shader(frag, GL_FRAGMENT_SHADER);
        
        GLuint program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        glGetProgramiv(program, GL_LINK_STATUS, &result);
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
       
        if (info_log_length > 0)
        {
            char* error_message = new char[info_log_length + 1];
            glGetProgramInfoLog(program, info_log_length, NULL, error_message);
            fprintf(stdout, "%s", error_message);
            delete[] error_message;
        }
        
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        
        return program;
    }

	GLuint load_texture(const unsigned char* data, int width, int height, GLuint format)
	{
		GLuint texture;
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);
        
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		return texture;
	}
    
    void bind_texture(GLuint texture)
    {
        if (current_texture != texture)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
        }
    }
    
    void set_blend_func(GLenum source, GLenum destination)
    {
        glBlendFunc(source, destination);
    }
    
    void draw_texture2d(float x, float y, float width, float height)
    {
        static const GLsizei size = 8;
        static GLfloat vertices[size];
        
        static const GLushort indices[size] = { 0, 1, 2, 2, 3, 0 };
        static const GLfloat texture_coords[] = { 0, 0, 1, 0, 1, -1, 0, -1, };
        
        vertices[0] = x;
        vertices[1] = y;
        vertices[2] = x + width;
        vertices[3] = y;
        vertices[4] = x + width;
        vertices[5] = y + height;
        vertices[6] = x;
        vertices[7] = y + height;
        
        glEnableVertexAttribArray(vertex_attribute::position);
        glEnableVertexAttribArray(vertex_attribute::texture_position);
        glEnable(GL_BLEND);
        
        GLuint index_buffer;
        glGenBuffers(1, &index_buffer);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLushort), indices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, buffers::position);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(vertex_attribute::position, 2, GL_FLOAT, GL_FALSE, 0, NULL);

        glBindBuffer(GL_ARRAY_BUFFER, buffers::texture_position);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texture_coords), texture_coords, GL_STATIC_DRAW);
        glVertexAttribPointer(vertex_attribute::texture_position, 2, GL_FLOAT, GL_FALSE, 0, NULL);

        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_SHORT, NULL);

        glDisableVertexAttribArray(vertex_attribute::position);
        glDisableVertexAttribArray(vertex_attribute::texture_position);
        glDisable(GL_BLEND);
        
        glDeleteBuffers(1, &index_buffer);
    }
    
    void delete_texture(GLuint texture)
    {
        glDeleteTextures(1, &texture);
    }
    
    void draw_line(float x1, float y1, float x2, float y2)
    {
        const GLfloat vertices[] =
        {
            x1, y1,
            x2, y2
        };
        
        glEnableVertexAttribArray(vertex_attribute::position);
        
        glBindBuffer(GL_ARRAY_BUFFER, buffers::position);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		glDrawArrays(GL_LINES, 0, 2);
        
		glDisableVertexAttribArray(vertex_attribute::position);
    }
    
    void draw_rect(float x, float y, float width, float height)
    {
        draw_line(x, y, x + width, y);
        draw_line(x + width, y, x + width, y + height);
        draw_line(x + width, y + height, x, y + height);
        draw_line(x, y + height, x, y);
    }
}
