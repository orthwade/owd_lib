#include "c_mat4_uniform.h"

namespace owd_lib
{
    c_mat4_uniform::c_mat4_uniform()
    {
        m_logger << "----c_mat4_uniform constructor START---- " << m_name << '\n';
        {
            set_uniform_name("u_mat4");
        }
        m_logger << "----c_mat4_uniform constructor OK---- " << m_name << '\n';
    }

    c_mat4_uniform::~c_mat4_uniform()
    {
        m_logger << "----c_mat4_uniform destructor START---- " << m_name << '\n';
        {

        }
        m_logger << "----c_mat4_uniform destructor OK---- " << m_name << '\n';
    }

    c_mat4_uniform::c_mat4_uniform(const c_mat4_uniform& other)
    {
        m_logger << "----Copy construction from [" << other.m_name << "] of [" << m_name << "] START----\n";
        {
            *this = other;
        }
        m_logger << "----Copy construction from [" << other.m_name << "] of [" << m_name << "] OK----\n";
    }

    c_mat4_uniform& owd_lib::c_mat4_uniform::operator=(const c_mat4_uniform& other)
    {
        m_logger << "----Assigning [" << other.m_name << "] to [" << m_name << "] START----\n";
        {
            if (this != &other)
            {
                m_name = other.m_name;
                m_logger = other.m_logger;
            }
        }
        m_logger << "----Assigning [" << other.m_name << "] to [" << m_name << "] OK----\n";
        return *this;
    }

    void c_mat4_uniform::init(uint32_t shader_program_id)
    {
        m_logger << m_name << "----Initializing mat4 uniform:\n";
        //m_logger << m_name << "----shader id: " << shader_program_id << ";    sampler id: " << m_sampler_id << '\n';
        {
            m_shader_program_id = shader_program_id;
            get_location();
            ASSERT(m_uniform_location != -1);
            auto gl_gloat_ptr = reinterpret_cast<const GLfloat*>(m_mat4());
            GL_CALL(glUniformMatrix4fv(m_uniform_location, 1, GL_FALSE, gl_gloat_ptr));
        }
        m_logger << m_name << "----Initializing colour uniform OK----\n";
    }

    void c_mat4_uniform::init(uint32_t shader_program_id, owd::c_mat4& glm_mat4)
    {
        m_logger << m_name << "----Initializing mat4 uniform:\n";
        //m_logger << m_name << "----shader id: " << shader_program_id << ";    sampler id: " << m_sampler_id << '\n';
        {
            m_shader_program_id = shader_program_id;
            m_mat4 = glm_mat4;
            get_location();
            ASSERT(m_uniform_location != -1);
            auto gl_gloat_ptr = reinterpret_cast<const GLfloat*>(m_mat4());
            GL_CALL(glUniformMatrix4fv(m_uniform_location, 1, GL_FALSE, gl_gloat_ptr));
        }
        m_logger << m_name << "----Initializing colour uniform OK----\n";
    }

    void c_mat4_uniform::set(owd::c_mat4& glm_mat4)
    {
        m_logger << m_name << "----Setting mat4 uniform:\n";
        //m_logger << m_name << "----glm_mat4: " << glm_mat4[0] << '\n';
        {
            //m_shader_program_id = shader_program_id;
            m_mat4 = glm_mat4;
            get_location();
            ASSERT(m_uniform_location != -1);
            auto gl_gloat_ptr = reinterpret_cast<const GLfloat*>(m_mat4());
            GL_CALL(glUniformMatrix4fv(m_uniform_location, 1, GL_FALSE, gl_gloat_ptr));
        }
        m_logger << m_name << "----Setting colour uniform OK----\n";
    }

}

