#include "c_colour_uniform.h"

namespace owd_lib
{
    c_colour_uniform::c_colour_uniform()
    {
        m_logger << "----c_colour_uniform constructor START---- " << m_name << '\n';
        {
            set_uniform_name("u_colour");
        }
        m_logger << "----c_colour_uniform constructor OK---- " << m_name << '\n';
    }

   c_colour_uniform::~c_colour_uniform()
    {
       m_logger << "----c_colour_uniform destructor START---- " << m_name << '\n';
       {

       }
       m_logger << "----c_colour_uniform destructor OK---- " << m_name << '\n';
    }

    c_colour_uniform::c_colour_uniform(const c_colour_uniform& other)
    {
        m_logger << "----Copy construction from [" << other.m_name << "] of [" << m_name << "] START----\n";
        {
            *this = other;
        }
        m_logger << "----Copy construction from [" << other.m_name << "] of [" << m_name << "] OK----\n";
    }

    c_colour_uniform& owd_lib::c_colour_uniform::operator=(const c_colour_uniform& other)
    {
        m_logger << "----Assigning [" << other.m_name << "] to [" << m_name << "] START----\n";
        {
            if (this != &other)
            {
                m_name              = other.m_name;
                m_logger            = other.m_logger;
                m_shader_program_id = other.m_shader_program_id;
                m_r                 = other.m_r;
                m_g                 = other.m_g;
                m_b                 = other.m_b;
                m_a                 = other.m_a;
                m_uniform_location  = other.m_uniform_location;
            }
        }
        m_logger << "----Assigning [" << other.m_name << "] to [" << m_name << "] OK----\n";
        return *this;
    }

  /*  void c_colour_uniform::set_name(std::wstring_view name)
    {
        m_logger << "----Setting name [" << name << "] to [" << m_name << "]----\n";
		{
			m_name = std::wstring(name);
		}
		m_logger << "----Setting name [" << name << "] to [" << m_name << "] OK----\n";
    }*/
    void c_colour_uniform::init(uint32_t shader_program_id)
    {
        //m_mtx.lock();
        {
            m_logger << m_name << "----Initializing colour uniform:\n";
            m_logger << m_name << "----shader id: " << shader_program_id << ";    red: " << m_r <<
                ";    green: " << m_g << ";    blue: " << m_b << ";    alpha: " << m_a << '\n';
            {
                m_shader_program_id = shader_program_id;
                get_location();
                ASSERT(m_uniform_location != -1);
                GL_CALL(glUniform4f(m_uniform_location, m_r, m_g, m_b, m_a));
            }
            m_logger << m_name << "----Initializing colour uniform OK----\n";
        }
        //m_mtx.unlock();
    }
    void c_colour_uniform::init(uint32_t shader_program_id, float r, float g, float b, float a)
    {
        //m_mtx.lock();
        {
            m_logger << m_name << "----Initializing colour uniform:\n";
            m_logger << m_name << "----shader id: " << shader_program_id << ";    red: " << r <<
                ";    green: " << g << ";    blue: " << b << ";    alpha: " << a << '\n';
            {
                m_shader_program_id = shader_program_id;
                m_r = r;
                m_g = g;
                m_b = b;
                m_a = a;

                get_location();
                ASSERT(m_uniform_location != -1);
                GL_CALL(glUniform4f(m_uniform_location, m_r, m_g, m_b, m_a));
            }
            m_logger << m_name << "----Initializing colour uniform OK----\n";
        }
        //m_mtx.unlock();
    }
    void c_colour_uniform::set(c_colour_uniform& other)
    {
        //m_mtx.lock();
        {
            m_logger << m_name << "----Setting colour uniform:\n";
            m_logger << m_name << "----shader id: " << other.m_shader_program_id << ";    red: " << other.m_r <<
                ";    green: " << other.m_g << ";    blue: " << other.m_b << ";    alpha: " << other.m_a << '\n';
            {
                *this = other;
                get_location();
                ASSERT(m_uniform_location != -1);
                GL_CALL(glUniform4f(m_uniform_location, m_r, m_g, m_b, m_a));
            }
            m_logger << m_name << "----Setting colour uniform OK----\n";
        }
        //m_mtx.unlock();
    }
    void c_colour_uniform::set(float red, float green, float blue, float alpha)
    {
        //m_mtx.lock();
        {
            m_logger << m_name << "----Setting colour uniform:\n";
            m_logger << m_name << "----shader id: " << m_shader_program_id << ";    red: " << red <<
                ";    green: " << green << ";    blue: " << blue << ";    alpha: " << alpha << '\n';
            {
               // m_shader_program_id = shader_program_id;
                m_r = red;
                m_g = green;
                m_b = blue;
                m_a = alpha;

                get_location();
                ASSERT(m_uniform_location != -1);
                GL_CALL(glUniform4f(m_uniform_location, m_r, m_g, m_b, m_a));
            }
            m_logger << m_name << "----Setting colour uniform OK----\n";
        }
        //m_mtx.unlock();
    }
    void c_colour_uniform::set(float red, float green, float blue, float alpha, uint32_t shader_program_id)
    {
        //m_mtx.lock();
        {
            m_logger << m_name << "----Setting colour uniform:\n";
            m_logger << m_name << "----shader id: " << shader_program_id << ";    red: " << red <<
                ";    green: " << green << ";    blue: " << blue << ";    alpha: " << alpha << '\n';
            {
                m_shader_program_id = shader_program_id;
                m_r = red;
                m_g = green;
                m_b = blue;
                m_a = alpha;

                get_location();
                ASSERT(m_uniform_location != -1);
                GL_CALL(glUniform4f(m_uniform_location, m_r, m_g, m_b, m_a));
            }
            m_logger << m_name << "----Setting colour uniform OK----\n";
        }
        //m_mtx.unlock();
    }
}

