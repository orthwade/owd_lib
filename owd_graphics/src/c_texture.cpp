#include "c_texture.h"

namespace owd_lib
{
    static int32_t init_stbi = c_texture::init_stbi();

    int32_t c_texture::init_stbi()
    {
        stbi_set_flip_vertically_on_load(1);
        return 1;
    }
    c_texture::c_texture()
    {
        init();
    }

    c_texture::c_texture(std::wstring_view filepath)
        :c_texture(filepath, filepath)
    {
    }

    c_texture::c_texture(std::wstring_view filepath, std::wstring_view name)
    {
        init();
        load(filepath, name);
    }

   c_texture::~c_texture()
    {
       terminate();
    }

    void c_texture::init()
    {
        GL_CALL(glGenTextures(1, &m_ogl_id));
    }

    void c_texture::terminate()
    {
        GL_CALL(glDeleteTextures(1, &m_ogl_id));
    }

    bool c_texture::load(std::wstring_view filepath)
    { 
        return load(filepath, filepath);
    }
    bool c_texture::load(std::wstring_view filepath, std::wstring_view name)
    {
        m_filepath = std::wstring(filepath);

        m_name = std::wstring(name);

        auto u8_filepath = owd::utf_8(m_filepath);

        m_data_buffer = stbi_load(u8_filepath.c_str(), &m_w, &m_h, &m_channels_count, 4);

        m_channels_count = 4;

        if (m_data_buffer)
        {
            //m_depth_bytes = m_depth_bits / 8;

            m_data_shared_ptr->resize
            (
                static_cast<size_t>(m_w) *
                static_cast<size_t>(m_h) *
                static_cast<size_t>(m_depth_bytes)
            );

            memcpy(data_raw_ptr(), m_data_buffer, size_bytes());

            stbi_image_free(m_data_buffer);

            GL_CALL(glActiveTexture(GL_TEXTURE0));
            GL_CALL(glBindTexture(GL_TEXTURE_2D, m_ogl_id));

            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
            GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

            GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_w, m_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data_raw_ptr()));

            m_state = enm_state::good;
        }
        else
        {
            m_state = enm_state::error;
        }

        return good();
    }
}

