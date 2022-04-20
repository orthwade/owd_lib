#include "c_vertex_array.h"

namespace owd_lib
{
    c_vertex_array::c_vertex_array()
    {
        m_logger << "----c_vertex_array constructor START---- " << m_name << '\n';
        {
            //GL_CALL(glGenVertexArrays(1, &m_ogl_id));
            //GL_CALL(glBindVertexArray(m_ogl_id));
            init();
        }
        m_logger << "----c_vertex_array constructor OK---- " << m_name << '\n';
    }

    c_vertex_array::~c_vertex_array()
    {
       m_logger << "----c_vertex_array destructor START---- " << m_name << '\n';
       {
           GL_CALL(glDeleteVertexArrays(1, &m_ogl_id));
       }
       m_logger << "----c_vertex_array destructor OK---- " << m_name << '\n';
    }

    c_vertex_array::c_vertex_array(const c_vertex_array& other)
    {
        m_logger << "----Copy construction from [" << other.m_name << "] of [" << m_name << "] START----\n";
        {
            *this = other;
        }
        m_logger << "----Copy construction from [" << other.m_name << "] of [" << m_name << "] OK----\n";
    }

    c_vertex_array& owd_lib::c_vertex_array::operator=(const c_vertex_array& other)
    {
        m_logger << "----Assigning [" << other.m_name << "] to [" << m_name << "] START----\n";
        {
            if (this != &other)
            {
                m_name      = other.m_name;
                m_logger    = other.m_logger;
                m_ogl_id    = other.m_ogl_id;
                m_index     = other.m_index;
                m_offset    = other.m_offset;
            }
        }
        m_logger << "----Assigning [" << other.m_name << "] to [" << m_name << "] OK----\n";
        return *this;
    }

    void c_vertex_array::set_name(std::wstring_view name)
    {
        m_logger << "----Setting name [" << name << "] to [" << m_name << "]----\n";
		{
			m_name = std::wstring(name);
		}
		m_logger << "----Setting name [" << name << "] to [" << m_name << "] OK----\n";
    }
    void c_vertex_array::init()
    {
        //m_mtx.lock();
        {
            m_logger << "----Initializing START---- " << m_name << '\n';
            {
                GL_CALL(glGenVertexArrays(1, &m_ogl_id));
                //GL_CALL(glBindVertexArray(m_ogl_id));

                //GL_CALL(glEnableVertexAttribArray(0));
                //GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
            }
            m_logger << "----Initializing OK---- " << m_name << '\n';
        }
        //m_mtx.unlock();
    }
    void c_vertex_array::terminate()
    {
        for (uint64_t i = 0; i != m_index; ++i)
        {
            GL_CALL(glDisableVertexAttribArray(i));
        }
        m_index = 0;
        m_offset = 0;
        GL_CALL(glDeleteVertexArrays(1, &m_ogl_id));
    }
    void c_vertex_array::bind()
    {
        //m_mtx.lock();
        {
            m_logger << "----Binding [" << m_name << "] ----\n";
            {
                GL_CALL(glBindVertexArray(m_ogl_id));
                /*for (uint64_t i = 0; i != m_index; ++i)
                {
                    GL_CALL(glEnableVertexAttribArray(i));
                }*/
            }
            m_logger << "----Binding [" << m_name << "] OK----\n";
        }
        //m_mtx.unlock();
    }
    void c_vertex_array::unbind()
    {
        //m_mtx.lock();
        {
            m_logger << "----Unbinding [" << m_name << "] ----\n";
            {
                /*for (uint64_t i = 0; i != m_index; ++i)
                {
                    GL_CALL(glDisableVertexAttribArray(i));
                }
                m_index = 0;
                m_offset = 0;*/
                //GL_CALL(glDeleteVertexArrays(1, &m_ogl_id));

                GL_CALL(glBindVertexArray(0));
                //GL_CALL(glDisableVertexAttribArray(m_index));
            }
            m_logger << "----Unbinding [" << m_name << "] OK----\n";
        }
        //m_mtx.unlock();
    }
    void c_vertex_array::add_buffer(c_vertex_buffer& vertex_buffer, c_vertex_buffer_layout& vertex_buffer_layout)
    {
        //m_mtx.lock();
        {
            m_logger << "----Adding buffer START----\n"; 
            {
                //vertex_buffer.unbind();
                //vertex_buffer.bind();
                bind();
                auto elements = vertex_buffer_layout.elements();

                c_vertex_buffer_element element{};

               // auto index_buffer = m_index;
                GL_CALL(glBufferData(GL_ARRAY_BUFFER, vertex_buffer.size(), vertex_buffer.data(), GL_DYNAMIC_DRAW));

                for (uint64_t i = 0; i != elements.size(); ++i)
                {
                    element = elements[i];

                    GL_CALL(glEnableVertexAttribArray(m_index));

                    GL_CALL(glVertexAttribPointer(m_index, element.m_count, element.m_type, element.m_normalized,
                        vertex_buffer_layout.stride(), reinterpret_cast<const void*>(m_offset)));

                    ++m_index;

                    m_offset += element.m_count * element.ogl_type_size_bytes();
                }
            }
            m_logger << "----Adding buffer OK----\n";
        }
        //m_mtx.unlock();
    }
    void c_vertex_array::set_data(c_vertex_buffer& vertex_buffer, c_vertex_buffer_layout& vertex_buffer_layout)
    {
        vertex_buffer.bind();
        GL_CALL(glBufferData(GL_ARRAY_BUFFER, vertex_buffer.size(), vertex_buffer.data(), GL_DYNAMIC_DRAW));
    }
   
    void c_vertex_array::reset()
    {
        //m_mtx.lock();
        {
            m_logger << "----Reset START----\n";
            {
                terminate();
                init();
            }
            m_logger << "----Reset OK----\n";
        }
        //m_mtx.unlock();
    }
}

