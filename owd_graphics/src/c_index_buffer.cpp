#include <algorithm>

#include "c_index_buffer.h"

namespace owd_lib
{
    c_index_buffer::c_index_buffer()
    {
        m_logger << "----c_index_buffer constructor START---- " << m_name << '\n';
        {
            init();
        }
        m_logger << "----c_index_buffer constructor OK---- " << m_name << '\n';
    }

   c_index_buffer::~c_index_buffer()
    {
       //m_mtx.lock();
       {
           m_logger << "----c_index_buffer destructor START---- " << m_name << '\n';
           {
               terminate();
           }
           m_logger << "----c_index_buffer destructor OK---- " << m_name << '\n';
       }
       //m_mtx.unlock();
    }

    c_index_buffer::c_index_buffer(const c_index_buffer& other)
    {
        m_logger << "----Copy construction from [" << other.m_name << "] of [" << m_name << "] START----\n";
        {
            *this = other;
        }
        m_logger << "----Copy construction from [" << other.m_name << "] of [" << m_name << "] OK----\n";
    }

    c_index_buffer& owd_lib::c_index_buffer::operator=(const c_index_buffer& other)
    {
        m_logger << "----Assigning [" << other.m_name << "] to [" << m_name << "] START----\n";
        {
            if (this != &other)
            {
                m_name = other.m_name;
                m_logger = other.m_logger;
                m_ogl_buffer_id = other.m_ogl_buffer_id;
                m_indices = other.m_indices;
            }
        }
        m_logger << "----Assigning [" << other.m_name << "] to [" << m_name << "] OK----\n";
        return *this;
    }

    void c_index_buffer::set_name(std::wstring_view name)
    {
        m_logger << "----Setting name [" << name << "] to [" << m_name << "]----\n";
		{
			m_name = std::wstring(name);
		}
		m_logger << "----Setting name [" << name << "] to [" << m_name << "] OK----\n";
    }
    void c_index_buffer::init()
    {
        //m_mtx.lock();
        {
            m_logger << "----initializing [" << m_name << "] ----\n";
            {
               // float* pos = m_vertex_positions.data();
               //
               // glGenBuffers(1, &m_ogl_buf_id);
               // glBindBuffer(GL_ARRAY_BUFFER, m_ogl_buf_id);
               // glBufferData(GL_ARRAY_BUFFER, m_vertex_positions.size() * sizeof(float), pos, GL_STATIC_DRAW);
               //
               // glEnableVertexAttribArray(0);
               //
               // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

                auto* indices = m_indices.data();

                GL_CALL(glGenBuffers(1, &m_ogl_buffer_id));
                GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ogl_buffer_id));
                GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint32_t), indices,
                    GL_DYNAMIC_DRAW));
                unbind();
               // glEnableVertexAttribArray(0);

                //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
            }
            m_logger << "----initializing [" << m_name << "] OK----\n";
        }
        //m_mtx.unlock();
    }
    void c_index_buffer::terminate()
    {
        GL_CALL(glDeleteBuffers(1, &m_ogl_buffer_id));
    }
   //void c_index_buffer::set_vertex_positions(std::vector<float>& input)
   //{
   //    //m_mtx.lock();
   //    {
   //        m_logger << "----Setting vertex positions [" << m_name << "] ----\n";
   //        {
   //            m_vertex_positions = input;
   //        }
   //        m_logger << "----Setting vertex positions [" << m_name << "] OK----\n";
   //    }
   //    //m_mtx.unlock();
   //}
    void c_index_buffer::set(const std::vector<uint32_t>& input)
    {
        //m_mtx.lock();
        {
            m_logger << "----Setting indices [" << m_name << "] ----\n";
            {
                m_indices = input;

                update_buffer_data();
            }
            m_logger << "----Setting indices [" << m_name << "] OK----\n";
        }
        //m_mtx.unlock();
    }
    void c_index_buffer::add(const std::vector<uint32_t>& input)
    {
        m_logger << "----Adding indices [" << m_name << "] ----\n";
        {
            m_indices.insert(m_indices.end(), input.begin(), input.end());
        }
        m_logger << "----Adding indices [" << m_name << "] OK----\n";
    }
    void c_index_buffer::add(const std::vector<uint32_t>& input, bool update_buffer_data_)
    {
        m_indices.insert(m_indices.end(), input.begin(), input.end());
     
        if (update_buffer_data_)
        {
            update_buffer_data();
        }
    }
    void c_index_buffer::update_buffer_data()
    {
        auto indices = m_indices.data();
        bind();
        GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint32_t), indices, GL_DYNAMIC_DRAW));
    }
    void c_index_buffer::bind()
    {
        //m_mtx.lock();
        {
            m_logger << "----Binding [" << m_name << "] ----\n";
            {
                GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ogl_buffer_id));
            }
            m_logger << "----Binding [" << m_name << "] OK----\n";
        }
        //m_mtx.unlock();
    }
    void c_index_buffer::unbind()
    {
        //m_mtx.lock();
        {
            m_logger << "----Unbinding [" << m_name << "] ----\n";
            {
                GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
            }
            m_logger << "----Unbinding [" << m_name << "] OK----\n";
        }
        //m_mtx.unlock();
    }
    gl_index_t c_index_buffer::max_index()
    {
        if (m_indices.empty())
        {
            return 0;
        }
        else
        {
            return *std::max_element(m_indices.begin(), m_indices.end());
        }
    }
}

