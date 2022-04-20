#include "c_vertex_buffer.h"

namespace owd_lib
{
    c_vertex_buffer::c_vertex_buffer()
    {
        //m_mtx.lock();
        {
            m_logger << "----c_vertex_buffer constructor START---- " << m_name << '\n';
            {
               //float* pos = m_vertex_positions.data();
               //
               //GL_CALL(glGenBuffers(1, &m_ogl_buffer_id));
               //GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_ogl_buffer_id));
               //GL_CALL(glBufferData(GL_ARRAY_BUFFER, m_vertex_positions.size() * sizeof(float), pos, GL_STATIC_DRAW));
               //
               //GL_CALL(glEnableVertexAttribArray(0));
               //GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
                init();
            }
            m_logger << "----c_vertex_buffer constructor OK---- " << m_name << '\n';
        }
        //m_mtx.unlock();
    }

    /*c_vertex_buffer::c_vertex_buffer(std::vector<float>& vertices)
    {
        //m_mtx.lock();
        {
            m_logger << "----c_vertex_buffer constructor START---- " << m_name << '\n';
            {
                m_vertex_positions = vertices;
                float* pos = m_vertex_positions.data();

                GL_CALL(glGenBuffers(1, &m_ogl_buf_id));
                GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_ogl_buf_id));
                GL_CALL(glBufferData(GL_ARRAY_BUFFER, m_vertex_positions.size() * sizeof(float), pos, GL_STATIC_DRAW));

                GL_CALL(glEnableVertexAttribArray(0));
                GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
            }
            m_logger << "----c_vertex_buffer constructor OK---- " << m_name << '\n';
        }
        //m_mtx.unlock();
    }*/

   c_vertex_buffer::~c_vertex_buffer()
    {
       //m_mtx.lock();
       {
           m_logger << "----c_vertex_buffer destructor START---- " << m_name << '\n';
           {
               GL_CALL(glDeleteBuffers(1, &m_ogl_id));
           }
           m_logger << "----c_vertex_buffer destructor OK---- " << m_name << '\n';
       }
       //m_mtx.unlock();
    }

    c_vertex_buffer::c_vertex_buffer(const c_vertex_buffer& other)
    {
        m_logger << "----Copy construction from [" << other.m_name << "] of [" << m_name << "] START----\n";
        {
            *this = other;
        }
        m_logger << "----Copy construction from [" << other.m_name << "] of [" << m_name << "] OK----\n";
    }

    c_vertex_buffer& owd_lib::c_vertex_buffer::operator=(const c_vertex_buffer& other)
    {
        m_logger << "----Assigning [" << other.m_name << "] to [" << m_name << "] START----\n";
        {
            if (this != &other)
            {
                m_name                  = other.m_name;
                m_logger                = other.m_logger;
                m_ogl_id                = other.m_ogl_id;
                //m_vertex_array_ogl_id   = other.m_vertex_array_ogl_id;
                m_vertex_positions_data = other.m_vertex_positions_data;
            }
        }
        m_logger << "----Assigning [" << other.m_name << "] to [" << m_name << "] OK----\n";
        return *this;
    }

    void c_vertex_buffer::set_name(std::wstring_view name)
    {
        //m_mtx.lock();
        {
            m_logger << "----Setting name [" << name << "] to [" << m_name << "]----\n";
            {
                m_name = std::wstring(name);
            }
            m_logger << "----Setting name [" << name << "] to [" << m_name << "] OK----\n";
        }
        //m_mtx.unlock();
    }
    void c_vertex_buffer::init()
    {
        //m_mtx.lock();
        {
            m_logger << "----c_vertex_buffer initializing START---- " << m_name << '\n';
            {
                //m_vertex_positions = vertices;
                //void* pos = m_vertex_positions_data->data();

                //GL_CALL(glGenVertexArrays(1, &m_vertex_array_ogl_id));
               // GL_CALL(glBindVertexArray(m_vertex_array_ogl_id));


                GL_CALL(glGenBuffers(1, &m_ogl_id));
                //GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_ogl_id));

                //GL_CALL(glBufferData(GL_ARRAY_BUFFER, m_vertex_positions_data->size() * sizeof(float), pos, GL_STATIC_DRAW));

                //GL_CALL(glEnableVertexAttribArray(0));
                //GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
                //auto ss = sizeof(float);
            }
            m_logger << "----c_vertex_buffer initializing OK---- " << m_name << '\n';
        }
        //m_mtx.unlock();
    }
    void c_vertex_buffer::terminate()
    {
        GL_CALL(glDeleteBuffers(1, &m_ogl_id));
    }
    void c_vertex_buffer::set(const std::vector<float>& input)
    {
        //m_mtx.lock();
        {
            m_logger << "----Setting vertex positions [" << m_name << "] ----\n";
            {
                if (input.size() > 0)
                {
                    size_t input_size_bytes = sizeof(float) * input.size();

                    m_vertex_positions_data->clear();

                    m_vertex_positions_data->resize(input_size_bytes);

                    auto input_data_ptr = reinterpret_cast<const void*>(input.data());
                    auto m_vertex_positions_data_ptr = reinterpret_cast<void*>(m_vertex_positions_data->data());

                    memcpy(m_vertex_positions_data_ptr, input_data_ptr, input_size_bytes);
                }
            }
            m_logger << "----Setting vertex positions [" << m_name << "] OK----\n";
        }
        //m_mtx.unlock();
    }
    void c_vertex_buffer::add(const std::vector<float>& input)
    {
        m_logger << "----Setting vertex positions [" << m_name << "] ----\n";
        {
            if (input.size() > 0)
            {
                size_t input_size_bytes = sizeof(float) * input.size();
                size_t content_old_size_bytes = m_vertex_positions_data->size();
                size_t content_new_size_bytes = content_old_size_bytes + input_size_bytes;

                m_vertex_positions_data->resize(content_new_size_bytes);

                auto input_data_ptr = reinterpret_cast<const void*>(input.data());

                auto m_vertex_positions_data_ptr = reinterpret_cast<char*>(m_vertex_positions_data->data());

                m_vertex_positions_data_ptr += content_old_size_bytes;

                memcpy(m_vertex_positions_data_ptr, input_data_ptr, input_size_bytes);
            }
        }
        m_logger << "----Setting vertex positions [" << m_name << "] OK----\n";
    }
    void c_vertex_buffer::bind()
    {
        //m_mtx.lock();
        {
            m_logger << "----Binding [" << m_name << "] ----\n";
            {
                GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_ogl_id));
            }
            m_logger << "----Binding [" << m_name << "] OK----\n";
        }
        //m_mtx.unlock();
    }
    void c_vertex_buffer::unbind()
    {
        //m_mtx.lock();
        {
            m_logger << "----Unbinding [" << m_name << "] ----\n";
            {
                GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
            }
            m_logger << "----Unbinding [" << m_name << "] OK----\n";
        }
        //m_mtx.unlock();
    }
}

