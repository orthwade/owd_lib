#include "c_graphic_batch_textured.h"

namespace owd_lib
{
    using owd::index_t;
    c_graphic_batch_textured::c_graphic_batch_textured()
        : c_graphic_batch_textured(0)
    {
    }
    c_graphic_batch_textured::c_graphic_batch_textured(uint16_t level)
        : m_level(level)
    {
        m_vertex_array.bind();
        m_vertex_buffer.bind();
        m_index_buffer.bind();

        m_vertex_buffer_layout.add_element(2);
        m_vertex_buffer_layout.add_element(2);
        m_vertex_buffer_layout.add_element(1);

        m_vertex_array.add_buffer(m_vertex_buffer, m_vertex_buffer_layout);

        m_should_update = true;
    }
    void c_graphic_batch_textured::add(g_unit_textured_t& unit)
    {
        m_vec.push_back(unit);
        m_should_update = true;
    }
    void c_graphic_batch_textured::draw()
    {
        m_vertex_array.bind();
        m_index_buffer.bind();
        update();
        for (index_t i = 0; i != m_vec.size(); ++i)
        {
            GL_CALL(glBindTextureUnit(i, m_vec[i]->get_texture()->gl_id()));
        }
        GL_CALL(glDrawElements(GL_TRIANGLES, indices_count(), GL_UNSIGNED_INT, nullptr));
    }
    g_unit_textured_t& c_graphic_batch_textured::get_unit(index_t index)
    {
        if (index < m_vec.size())
        {
            return m_vec[index];
        }
        else
        {
            return empty_unit();
        }
    }
    g_unit_textured_t& c_graphic_batch_textured::get_last_unit()
    {
        if (!m_vec.empty())
        {
            return m_vec.back();
        }
        else
        {
            return empty_unit();
        }
    }
    void c_graphic_batch_textured::erase(index_t index)
    {
        if (index < m_vec.size())
        {
            auto iter = m_vec.begin();
            iter += index;
            m_vec.erase(iter);
            m_should_update = true;
        }
    }
    void c_graphic_batch_textured::update()
    {
        if (m_vec.empty())
        {

        }
        else
        {
            for (index_t i = 0; i != m_vec.size(); ++i)
            {
                if (m_vec[i]->m_should_update)
                {
                    this->m_should_update = true;
                    break;
                }
            }
            if (this->m_should_update)
            {
                // Deleting if set to delete
                for (index_t i = 0; i < m_vec.size(); ++i)
                {
                    if (m_vec[i]->deleted())
                    {
                        auto iter = m_vec.begin();
                        iter += i;
                        m_vec.erase(iter);
                        m_should_update = true;
                        i = 0;
                    }
                }
                m_vertices_buffer.clear();
                m_indices_buffer.clear();
                gl_index_t max_index_ = 0;
                for (index_t i = 0; i != m_vec.size(); ++i)
                {
                    m_vec[i]->m_index_in_batch = i;
                    m_vec[i]->m_index = i;
                    auto vertices_ = m_vec[i]->vertices();
                    m_vertices_buffer.insert
                    (m_vertices_buffer.end(), vertices_.begin(), vertices_.end());
                    if (m_indices_buffer.empty())
                    {
                    }
                    else
                    {
                        max_index_ = *std::max_element(m_indices_buffer.begin(), m_indices_buffer.end());
                    }
                    auto indices_ = m_vec[i]->indices_batch(max_index_);
                    m_indices_buffer.insert
                    (m_indices_buffer.end(), indices_.begin(), indices_.end());
                    m_vec[i]->m_should_update = false;
                }
                m_vertex_buffer.set(m_vertices_buffer);
                m_index_buffer.set(m_indices_buffer);

                m_vertex_array.set_data(m_vertex_buffer, m_vertex_buffer_layout);

                m_should_update = false;
            }
        }
    }
}

