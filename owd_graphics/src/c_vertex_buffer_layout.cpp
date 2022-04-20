#include "c_vertex_buffer_layout.h"

namespace owd_lib
{
    c_vertex_buffer_layout::c_vertex_buffer_layout()
    {
        m_logger << "----c_vertex_buffer_layout constructor START---- " << m_name << '\n';
        {

        }
        m_logger << "----c_vertex_buffer_layout constructor OK---- " << m_name << '\n';
    }

   c_vertex_buffer_layout::~c_vertex_buffer_layout()
    {
       m_logger << "----c_vertex_buffer_layout destructor START---- " << m_name << '\n';
       {

       }
       m_logger << "----c_vertex_buffer_layout destructor OK---- " << m_name << '\n';
    }

    c_vertex_buffer_layout::c_vertex_buffer_layout(const c_vertex_buffer_layout& other)
    {
        m_logger << "----Copy construction from [" << other.m_name << "] of [" << m_name << "] START----\n";
        {
            *this = other;
        }
        m_logger << "----Copy construction from [" << other.m_name << "] of [" << m_name << "] OK----\n";
    }

    c_vertex_buffer_layout& owd_lib::c_vertex_buffer_layout::operator=(const c_vertex_buffer_layout& other)
    {
        m_logger << "----Assigning [" << other.m_name << "] to [" << m_name << "] START----\n";
        {
            if (this != &other)
            {
                m_name      = other.m_name;
                m_logger    = other.m_logger;
                m_stride    = other.m_stride;
                m_elements  = other.m_elements;
            }
        }
        m_logger << "----Assigning [" << other.m_name << "] to [" << m_name << "] OK----\n";
        return *this;
    }

    void c_vertex_buffer_layout::set_name(std::wstring_view name)
    {
        m_logger << "----Setting name [" << name << "] to [" << m_name << "]----\n";
		{
			m_name = std::wstring(name);
		}
		m_logger << "----Setting name [" << name << "] to [" << m_name << "] OK----\n";
    }
}

