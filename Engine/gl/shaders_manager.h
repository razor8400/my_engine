#pragma once

#include "gl.h"

namespace gl
{
    class shader_program;
    typedef std::shared_ptr<shader_program> shader_program_ptr;

    class shaders_manager
    {
    public:
        static shaders_manager& instance();

        template<class T>
        static shader_program_ptr create_gl_program(const char* vert, const char* frag);

        const shader_program_ptr& get_program(const std::string& key) const;
        
        void compile_default_shaders();
        void add_to_cache(const shader_program_ptr& program, const std::string& key);
    private:
        shaders_manager();

        std::map<std::string, shader_program_ptr> m_cache;
    };
}
