#include "c_glsl_uniform.h"

namespace owd_lib
{
    c_glsl_uniform::c_glsl_uniform()
    {
        m_logger << "----c_glsl_uniform constructor START---- " << m_object_name << '\n';
        {

        }
        m_logger << "----c_glsl_uniform constructor OK---- " << m_object_name << '\n';
    }

   c_glsl_uniform::~c_glsl_uniform()
    {
       m_logger << "----c_glsl_uniform destructor START---- " << m_object_name << '\n';
       {

       }
       m_logger << "----c_glsl_uniform destructor OK---- " << m_object_name << '\n';
    }

    c_glsl_uniform::c_glsl_uniform(const c_glsl_uniform& other)
    {
        m_logger << "----Copy construction from [" << other.m_object_name << "] of [" << m_object_name << "] START----\n";
        {
            *this = other;
        }
        m_logger << "----Copy construction from [" << other.m_object_name << "] of [" << m_object_name << "] OK----\n";
    }

    c_glsl_uniform& owd_lib::c_glsl_uniform::operator=(const c_glsl_uniform& other)
    {
        m_logger << "----Assigning [" << other.m_object_name << "] to [" << m_object_name << "] START----\n";
        {
            if (this != &other)
            {
                m_object_name       = other.m_object_name;
                m_uniform_name      = other.m_uniform_name;
                m_logger            = other.m_logger;
                m_shader_program_id = other.m_shader_program_id;
                m_uniform_location  = other.m_uniform_location;
            }
        }
        m_logger << "----Assigning [" << other.m_object_name << "] to [" << m_object_name << "] OK----\n";
        return *this;
    }

    void c_glsl_uniform::set_uniform_name(std::string_view name)
    {
        m_uniform_name = std::string(name);
    }

    int32_t c_glsl_uniform::get_location()
    {
        if (m_uniform_location == -1)
        {
            GL_CALL(m_uniform_location = glGetUniformLocation(m_shader_program_id, m_uniform_name.c_str()));
        }
        return m_uniform_location;
    }
}