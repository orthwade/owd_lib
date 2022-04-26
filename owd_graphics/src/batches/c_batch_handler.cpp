#include "c_batch_handler.h"

namespace owd_lib
{
    s_level& c_batch_handler::get_level(uint16_t level)
    {
        std::lock_guard lock{ m_mtx };
        if (level < m_levels.size())
        {
        }
        else
        {
            m_levels.resize(static_cast<size_t>(level) + 1);
        }
        return m_levels[level];
    }
    
    using owd::index_t;
    using owd::cos_d;
    using owd::sin_d;
    c_batch_handler* c_batch_handler::m_singleton = nullptr;

    c_batch_handler* owd_lib::c_batch_handler::get_instance()
    {
        if (m_singleton == nullptr)
        {
            m_singleton = new c_batch_handler();
        }

        return m_singleton;
    }
    void c_batch_handler::terminate()
    {
        if (m_singleton == nullptr)
        {

        }
        else
        {
            delete m_singleton;
            m_singleton = nullptr;
        }
    }
    c_batch_handler::c_batch_handler()
    {
        // 1. Coloured
        m_max_vertices = gl_int32_param(GL_MAX_ELEMENTS_VERTICES);
        m_max_indices = gl_int32_param(GL_MAX_ELEMENTS_INDICES);

        auto shaders = c_shader_bank::get_instance();
        shaders->load(L"rsc/shaders/batch_coloured.glsl", L"batch_coloured");

        m_shader_coloured = shaders->by_filepath(L"rsc/shaders/batch_coloured.glsl");

        m_shader_coloured->bind();

        m_mat4_uniform_coloured.set_uniform_name("u_aspect_ratio_projection_matrix");

        m_projection.set_aspect_ratio(m_window->aspect_ratio());
        m_mat4_uniform_coloured.init(m_shader_coloured->shader_program_id(), m_projection);
        // 2. Textured
        shaders->load(L"rsc/shaders/batch_textured.glsl", L"batch_textured");
        m_shader_textured = shaders->by_filepath(L"rsc/shaders/batch_textured.glsl");
        m_shader_textured->bind();

        GL_CALL(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_max_texture_image_units));

        m_mat4_uniform_textured.set_uniform_name("u_aspect_ratio_projection_matrix");
        m_mat4_uniform_textured.init(m_shader_textured->shader_program_id(), m_projection);

        m_texture_uniform.set_uniform_name("u_textures");

        std::vector<int32_t> samplers{};
        for (index_t i = 0; i != 128; ++i)
        {
            samplers.push_back(i);
        }
        m_texture_uniform.init(m_shader_textured->shader_program_id(), samplers);
    }
    void* c_batch_handler::add_textured_main_thread(float centre_x, float centre_y, float width, float height, texture_t& texture, uint16_t level)
    {
        auto rect = std::make_shared<c_graphic_unit_textured>(centre_x, centre_y, width, height, texture, level);
        return add_main_thread(rect);
    }
    c_batch_handler::~c_batch_handler()
    {
    }

    void* c_batch_handler::add(const std::vector<float>& positions, const std::vector<uint32_t>& indices,
        float r, float g, float b, float a, uint16_t l)
    {
        void* result = nullptr;
        auto unit = std::make_shared<c_graphic_unit_lib>(positions, indices, r, g, b, a, l);
        {
            std::lock_guard lock{ m_mtx };
            m_list_unit.push_back(unit);
            result = m_list_unit.back().get();
        }
        return result;
    }

    void* c_batch_handler::add(float x, float y, float w, float h,
        float r, float g, float b, float a, uint16_t l)
    {
        void* result = nullptr;
        vertices_t positions =
        {
            x + -w / 2.0f, y + -h / 2.0f,
            x +  w / 2.0f, y + -h / 2.0f,
            x +  w / 2.0f, y +  h / 2.0f,
            x + -w / 2.0f, y +  h / 2.0f
        };
        gl_indices_t indices = { 0, 1, 2, 2, 3, 0 };
        auto unit = std::make_shared<c_graphic_unit_lib>(positions, indices, r, g, b, a, l);
        {
            std::lock_guard lock{ m_mtx };
            m_list_unit.push_back(unit);
            result = m_list_unit.back().get();
        }
        return result;
    }

    void* c_batch_handler::add(float x, float y, float radius,
        float r, float g, float b, float a, uint16_t l)
    {
        void* result = nullptr;

        vertices_t positions{};
        gl_indices_t indices{};
        uint16_t triangles_count = 100;
        float angle_step = 360.0f / triangles_count;
        float angle = 90.0f + angle_step / 2.0f;

        positions.push_back(x);
        positions.push_back(y);

        for (uint16_t i = 0; i != triangles_count; ++i)
        {
            positions.push_back(x + radius * cos_d(angle));
            positions.push_back(y + radius * sin_d(angle));

            angle -= angle_step;
        }

        for (index_t i = 0; i < triangles_count; ++i)
        {
            indices.push_back(0);
            indices.push_back(i + 1);
            indices.push_back(i + 2);
        }
        indices.back() = 1;

        auto unit = std::make_shared<c_graphic_unit_lib>(positions, indices, r, g, b, a, l);
        {
            std::lock_guard lock{ m_mtx };
            m_list_unit.push_back(unit);
            result = m_list_unit.back().get();
        }
        return result;
    }

    void* c_batch_handler::add(float x, float y, float w, float h,
        std::wstring_view t, uint16_t l)
    {
        void* result = nullptr;
        auto texture = c_texture_bank::get_instance()->get(t);
        auto unit = std::make_shared<c_graphic_unit_textured>(x, y, w, h, texture, l);
        {
            std::lock_guard lock{ m_mtx };
            m_list_unit_textured.push_back(unit);
            result = m_list_unit_textured.back().get();
        }
        return result;
    }
    void c_batch_handler::update()
    {
        std::lock_guard lock(m_mtx);
        if (!m_list_unit.empty())
        {
            for (auto& unit : m_list_unit)
            {
                add_main_thread(unit);
            }
            m_list_unit.clear();
        }
        if (!m_list_unit_textured.empty())
        {
            for (auto& unit : m_list_unit_textured)
            {
                add_main_thread(unit);
            }
            m_list_unit_textured.clear();
        }
    }
    void c_batch_handler::clear()
    {
        m_levels.clear();
    }
    void c_batch_handler::draw()
    {
        for (index_t i = 0; i != m_levels.size(); ++i)
        {
            m_shader_coloured->bind();
            for (index_t ii = 0; ii != m_levels[i].batches.size(); ++ii)
            {
                m_levels[i].batches[ii]->draw();
            }
            m_shader_textured->bind();

            for (index_t ii = 0; ii != m_levels[i].batches_textured.size(); ++ii)
            {
                m_levels[i].batches_textured[ii]->draw();
            }
        }
    }
    void* c_batch_handler::add_main_thread(g_unit_t& unit)
    {
        std::lock_guard lock{m_mtx};

        auto& level = get_level(unit->level());
        auto& batches_ = level.batches;
        if (batches_.empty())
        {
            batches_.push_back(std::make_shared<c_graphic_batch>());
        }
        auto& batch_ = batches_.back();
        if (units_count_exceeds(batch_, unit))
        {
            batches_.push_back(std::make_shared<c_graphic_batch>());
            batch_ = batches_.back();
        }
        batch_->add(unit);

        return batch_->get_last_unit().get();
    }
    void* c_batch_handler::add_main_thread(g_unit_textured_t& unit)
    {
        auto& level = get_level(unit->level());
        auto& batches_ = level.batches_textured;
        if (batches_.empty())
        {
            batches_.push_back(std::make_shared<c_graphic_batch_textured>());
        }
        auto& batch_ = batches_.back();
        if (batch_->get_vec().size() >= m_max_texture_image_units)
        {
            batches_.push_back(std::make_shared<c_graphic_batch_textured>());
            batch_ = batches_.back();
        }
        batch_->add(unit);

        return batch_->get_last_unit().get();
    }
    bool c_batch_handler::vertices_exceed(g_batch_t& batch, g_unit_t& unit)
    {
        bool result = false;
        if (batch->vertices_count() + unit->vertices().size() > m_max_vertices)
        {
            result = true;
        }
        return result;
    }
    void* c_batch_handler::add_rect_main_thread(float centre_x, float centre_y, float width, float height, 
        float red, float green, float blue, float alpha, uint16_t level)
    {
        vertices_t positions =
        {
            centre_x + -width / 2.0f, centre_y + -height / 2.0f,
            centre_x + width / 2.0f, centre_y + -height / 2.0f,
            centre_x + width / 2.0f, centre_y + height / 2.0f,
            centre_x + -width / 2.0f, centre_y + height / 2.0f
        };
        gl_indices_t indices = { 0, 1, 2, 2, 3, 0 };

        auto rect = std::make_shared<c_graphic_unit_lib>(positions, indices, red, green, blue, alpha, level);
        return add_main_thread(rect);
    }
    bool c_batch_handler::indices_exceed(g_batch_t& batch, g_unit_t& unit)
    {
        bool result = false;
        if (batch->indices_count() + unit->indices_no_batch().size() > m_max_indices)
        {
            result = true;
        }
        return result;
    }
    bool c_batch_handler::units_count_exceeds(g_batch_t& batch, g_unit_t& unit)
    {
        return (vertices_exceed(batch, unit) || indices_exceed(batch, unit));
    }

    void* c_batch_handler::add_circle_main_thread(float centre_x, float centre_y, float radius, float red, float green, float blue, float alpha, uint16_t level)
    {
        vertices_t positions{};
        gl_indices_t indices{};
        uint16_t triangles_count = 100;
        float angle_step = 360.0f / triangles_count;
        float angle = 90.0f + angle_step / 2.0f;

        positions.push_back(centre_x);
        positions.push_back(centre_y);

        for (uint16_t i = 0; i != triangles_count; ++i)
        {
            positions.push_back(centre_x + radius * cos_d(angle));
            positions.push_back(centre_y + radius * sin_d(angle));

            angle -= angle_step;
        }

        for (index_t i = 0; i < triangles_count; ++i)
        {
            indices.push_back(0);
            indices.push_back(i + 1);
            indices.push_back(i + 2);
        }
        indices.back() = 1;

        auto circle = std::make_shared<c_graphic_unit_lib>(positions, indices, red, green, blue, alpha, level);
        return add_main_thread(circle);
    }
    /*void* c_batch_handler::add(g_unit_t& unit)
    {
        auto& level = get_level(unit->level());
        auto& batches_ = level.batches;
        if (batches_.empty())
        {
            batches_.push_back(std::make_shared<c_graphic_batch>());
        }
        auto& batch_ = batches_.back();
        if (units_count_exceeds(batch_, unit))
        {
            batches_.push_back(std::make_shared<c_graphic_batch>());
            batch_ = batches_.back();
        }
        batch_->add(unit);

        return batch_->get_last_unit().get();
    }
    void* c_batch_handler::add(g_unit_textured_t& unit)
    {
        auto& level = get_level(unit->level());
        auto& batches_ = level.batches_textured;
        if (batches_.empty())
        {
            batches_.push_back(std::make_shared<c_graphic_batch_textured>());
        }
        auto& batch_ = batches_.back();
        if (batch_->get_vec().size() >= m_max_texture_image_units)
        {
            batches_.push_back(std::make_shared<c_graphic_batch_textured>());
            batch_ = batches_.back();
        }
        batch_->add(unit);

        return batch_->get_last_unit().get();
    }
    void* c_batch_handler::add_rect(float centre_x, float centre_y, float width, float height,
        float red, float green, float blue, float alpha, uint16_t level)
    {
        vertices_t positions =
        {
            centre_x + -width / 2.0f, centre_y + -height / 2.0f,
            centre_x +  width / 2.0f, centre_y + -height / 2.0f,
            centre_x +  width / 2.0f, centre_y +  height / 2.0f,
            centre_x + -width / 2.0f, centre_y +  height / 2.0f
        };
        gl_indices_t indices = { 0, 1, 2, 2, 3, 0 };

        auto rect = std::make_shared<c_graphic_unit_lib>(positions, indices, red, green, blue, alpha, level);
        return add(rect);
    }
    void* c_batch_handler::add_circle(float centre_x, float centre_y, float radius,
        float red, float green, float blue, float alpha, uint16_t level)
    {
        vertices_t positions{};
        gl_indices_t indices{};
        uint16_t triangles_count = 100;
        float angle_step = 360.0f / triangles_count;
        float angle = 90.0f + angle_step / 2.0f;

        positions.push_back(centre_x);
        positions.push_back(centre_y);

        for (uint16_t i = 0; i != triangles_count; ++i)
        {
            positions.push_back(centre_x + radius * cos_d(angle));
            positions.push_back(centre_y + radius * sin_d(angle));

            angle -= angle_step;
        }

        for (index_t i = 0; i < triangles_count; ++i)
        {
            indices.push_back(0);
            indices.push_back(i + 1);
            indices.push_back(i + 2);
        }
        indices.back() = 1;

        auto circle = std::make_shared<c_graphic_unit_lib>(positions, indices, red, green, blue, alpha, level);
        return add(circle);
    }
    void* c_batch_handler::add_textured(float centre_x, float centre_y, float width, float height,
        texture_t& texture, uint16_t level)
    {
        auto rect = std::make_shared<c_graphic_unit_textured>(centre_x, centre_y, width, height, texture, level);
        return add(rect);
    }*/
}

