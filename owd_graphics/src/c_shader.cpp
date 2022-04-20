#include "c_shader.h"

namespace owd_lib
{
    c_shader::c_shader()
    {
        m_logger << "----c_basic_shader constructor START---- " << m_name << '\n';
        {
            init();
        }
        m_logger << "----c_basic_shader constructor OK---- " << m_name << '\n';
    }

    c_shader::c_shader(std::wstring_view filepath)
    {
        init();
        load(filepath);
    }

   c_shader::~c_shader()
    {
       m_logger << "----c_basic_shader destructor START---- " << m_name << '\n';
       {
           terminate();
       }
       m_logger << "----c_basic_shader destructor OK---- " << m_name << '\n';
    }


   
    bool c_shader::load(std::wstring_view filepath)
    {
        return load(filepath, filepath);
    }
    bool c_shader::load(std::wstring_view filepath, std::wstring_view name)
    {
        bool result = false;
        std::string shader_file_str{};
        m_filepath = filepath;
        m_ifstream().open(m_filepath);
        {
            result = m_ifstream().good();

            if (result)
            {
                shader_file_str.assign(std::istreambuf_iterator<char>(m_ifstream()), std::istreambuf_iterator<char>());
                m_logger << "----Loading file SUCCESS----\n";
                m_state = enm_state::good;
            }
            else
            {
                m_state = enm_state::error;
                m_logger << "----Loading file ERROR----\n";
            }
        }
        m_ifstream().close();

        m_filepath = std::wstring(filepath);

        m_name = std::wstring(name);

        for (uint16_t i = 0; i != m_array_gl_shader_struct.size(); ++i)
        {
            auto& gl_shader_struct = m_array_gl_shader_struct[i];

            gl_shader_struct.m_enabled = false;

            auto start_position = shader_file_str.find(gl_shader_struct.m_start_delimiter);

            if (start_position != std::string::npos)
            {
                auto end_position = shader_file_str.find(m_array_gl_shader_struct[i].m_end_delimiter);

                if (end_position != std::string::npos)
                {
                    start_position += gl_shader_struct.m_start_delimiter.size();

                    gl_shader_struct.m_string = shader_file_str.substr(start_position, end_position - start_position);

                    result = true;

                    gl_shader_struct.m_enabled = true;
                }
            }
        }

        compile();
        return result;
    }
    void c_shader::init()
    {
        set_name(L"shader");
        m_logger.set_name(L"shader_logger");
        if (m_shader_program_id == 0)
        {
            GL_CALL(m_shader_program_id = glCreateProgram());
        }
    }
    //void c_shader::load_vertex_shader(std::wstring_view filepath)
    //{
    //    //m_mtx.lock();
    //    {
    //        m_logger << "----Loading vertex shader from [" << filepath << "] to [" << m_name << "]----\n";
    //        {
    //            m_vertex_shader_str = text_file_to_string(filepath);
    //            //m_compile();
    //        }
    //        m_logger << "----Loading vertex shader from [" << filepath << "] to [" << m_name << "]----OK\n";
    //    }
    //    //m_mtx.unlock();
    //}
    //void c_shader::load_fragment_shader(std::wstring_view filepath)
    //{
    //    //m_mtx.lock();
    //    {
    //        m_logger << "----Loading fragment shader from [" << filepath << "] to [" << m_name << "]----\n";
    //        {
    //            m_fragment_shader_str = text_file_to_string(filepath);
    //            //m_compile();
    //        }
    //        m_logger << "----Loading fragment shader from [" << filepath << "] to [" << m_name << "]----OK\n";
    //    }
    //    //m_mtx.unlock();
    //}
    //void c_shader::set_vertex_shader(std::string_view shader_str)
    //{
    //    //m_mtx.lock();
    //    {
    //        m_logger << "----Setting vertex shader----\n";
    //        {
    //            m_vertex_shader_str = std::string(shader_str);
    //        }
    //        m_logger << "----Setting vertex shader----OK\n";
    //    }
    //    //m_mtx.unlock();
    //}
    //void c_shader::set_fragment_shader(std::string_view shader_str)
    //{
    //    //m_mtx.lock();
    //    {
    //        m_logger << "----Setting fragment shader----\n";
    //        {
    //            m_fragment_shader_str = std::string(shader_str);
    //        }
    //        m_logger << "----Setting fragment shader----OK\n";
    //    }
    //    //m_mtx.unlock();
    //}
    void c_shader::terminate()
    {
        GL_CALL(glDeleteProgram(m_shader_program_id));
        m_shader_program_id = 0;
    }
    void c_shader::bind()
    {
        GL_CALL(glUseProgram(m_shader_program_id));
    }
    void c_shader::unbind()
    {
        GL_CALL(glUseProgram(0))
    }
    uint32_t c_shader::shader_program_id()
    {
        return m_shader_program_id;
    }
    void c_shader::compile()
    {
        //m_mtx.lock();
        {
            m_logger << "----Compiling basic shader----\n";
            {
                if (m_shader_program_id != 0)
                {
                    for (uint16_t i = 0; i != m_array_gl_shader_struct.size(); ++i)
                    {
                        auto& gl_shader_struct = m_array_gl_shader_struct[i];
                        if (gl_shader_struct.m_enabled)
                        {
                            GL_CALL(gl_shader_struct.m_gl_shader_id = glCreateShader(gl_shader_struct.m_gl_code));
                            const char* string = gl_shader_struct.m_string.c_str();
                            GL_CALL(glShaderSource(gl_shader_struct.m_gl_shader_id, 1, &(string), nullptr));
                            GL_CALL(glCompileShader(gl_shader_struct.m_gl_shader_id));
                            GL_CALL(glAttachShader(m_shader_program_id, gl_shader_struct.m_gl_shader_id));
                        }
                    }

                    GL_CALL(glLinkProgram(m_shader_program_id));

                    GL_CALL(glValidateProgram(m_shader_program_id));

                    for (uint16_t i = 0; i != m_array_gl_shader_struct.size(); ++i)
                    {
                        auto& gl_shader_struct = m_array_gl_shader_struct[i];
                        if (gl_shader_struct.m_enabled)
                        {
                            GL_CALL(glDeleteShader(gl_shader_struct.m_gl_shader_id));
                        }
                    }

                    GL_CALL(glUseProgram(m_shader_program_id));
                }
            }
            m_logger << "----Compiling basic shader OK----\n";
        }
        //m_mtx.unlock();
    }
}

