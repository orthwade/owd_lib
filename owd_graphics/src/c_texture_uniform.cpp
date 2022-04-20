#include "c_texture_uniform.h"

namespace owd_lib
{
    c_texture_uniform::c_texture_uniform()
    {
        m_logger << "----c_texture_uniform constructor START---- " << m_name << '\n';
        {
            set_uniform_name("u_texture");
        }
        m_logger << "----c_texture_uniform constructor OK---- " << m_name << '\n';
    }

   c_texture_uniform::~c_texture_uniform()
    {
       m_logger << "----c_texture_uniform destructor START---- " << m_name << '\n';
       {

       }
       m_logger << "----c_texture_uniform destructor OK---- " << m_name << '\n';
    }

    c_texture_uniform::c_texture_uniform(const c_texture_uniform& other)
    {
        m_logger << "----Copy construction from [" << other.m_name << "] of [" << m_name << "] START----\n";
        {
            *this = other;
        }
        m_logger << "----Copy construction from [" << other.m_name << "] of [" << m_name << "] OK----\n";
    }

    c_texture_uniform& owd_lib::c_texture_uniform::operator=(const c_texture_uniform& other)
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

    void c_texture_uniform::init(uint32_t shader_program_id)
    {
        m_logger << m_name << "----Initializing texture uniform:\n";
        m_logger << m_name << "----shader id: " << shader_program_id << ";    sampler id: " << m_sampler_id << '\n';
        {
            m_shader_program_id = shader_program_id;
            get_location();
            ASSERT(m_uniform_location != -1);
            GL_CALL(glUniform1i(m_uniform_location, m_sampler_id));
        }
        m_logger << m_name << "----Initializing colour uniform OK----\n";
    }

    void c_texture_uniform::init(uint32_t shader_program_id, int32_t sampler_id)
    {
        m_logger << m_name << "----Initializing texture uniform:\n";
        m_logger << m_name << "----shader id: " << shader_program_id << ";    sampler id: " << m_sampler_id << '\n';
        {
            m_shader_program_id = shader_program_id;
            m_sampler_id = sampler_id;
            get_location();
            ASSERT(m_uniform_location != -1);
            GL_CALL(glUniform1i(m_uniform_location, m_sampler_id));
        }
        m_logger << m_name << "----Initializing colour uniform OK----\n";
    }

    void c_texture_uniform::init(uint32_t shader_program_id, std::vector<int32_t> vec_sampler_id)
    {
        m_logger << m_name << "----Initializing texture uniform:\n";
        m_logger << m_name << "----shader id: " << shader_program_id << ";    sampler id: " << m_sampler_id << '\n';
        {
            m_shader_program_id = shader_program_id;
            m_vec_sampler_id = vec_sampler_id;
            get_location();
            ASSERT(m_uniform_location != -1);
            GL_CALL(glUniform1iv(m_uniform_location, m_vec_sampler_id.size(), m_vec_sampler_id.data()));
        }
        m_logger << m_name << "----Initializing colour uniform OK----\n";
    }

    void c_texture_uniform::set(int32_t sampler_id)
    {
        m_logger << m_name << "----Setting texture uniform:\n";
        m_logger << m_name << "----sampler_id id: " << m_sampler_id << '\n';
        {
            //m_shader_program_id = shader_program_id;
            m_sampler_id = sampler_id;
            get_location();
            ASSERT(m_uniform_location != -1);
            GL_CALL(glUniform1i(m_uniform_location, m_sampler_id));
        }
        m_logger << m_name << "----Setting colour uniform OK----\n";
    }
}