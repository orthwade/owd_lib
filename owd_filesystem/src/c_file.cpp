#include "c_file.h"
#include <string_view>

namespace owd_lib
{
    c_file::c_file()
    {
        set_name(L"file_object");
    }
    bool c_file::load(std::wstring_view filepath)
    {
        return load(filepath, filepath);
    }
    bool c_file::load(std::wstring_view filepath, std::wstring_view name)
    { 
        return load_default(filepath, name);
    }
    bool c_file::save(std::wstring_view filepath)
    {
        return save_default(filepath);
    }
    bool c_file::good() const
    {
        return ((m_state == enm_state::not_loaded) || (m_state == enm_state::good));
    }
    std::wstring_view c_file::filepath()
    {
        return m_filepath;
    }
    void c_file::reset()
    {
        *this = c_file();
    }
    bool c_file::load_default(std::wstring_view filepath)
    {
        return load_default(filepath, filepath);
    }
    bool c_file::load_default(std::wstring_view filepath, std::wstring_view name)
    {
        bool result = false;
        set_name(name);
        m_filepath = filepath;
        m_ifstream().open(m_filepath, std::ios::binary);
        {
            result = m_ifstream().good();

            if (result)
            {
                m_ifstream().seekg(0, std::ios::end);
                    auto file_size_bytes = m_ifstream().tellg();
                m_ifstream().seekg(0, std::ios::beg);

                auto file_object = std::make_shared<bytes_t>();

                file_object->resize(file_size_bytes);

                m_ifstream().read(reinterpret_cast<char*>(file_object->data()), file_size_bytes);

                m_data_shared_ptr = file_object;

                m_state = enm_state::good;
                
                auto extenstion_delimiter = m_filepath.rfind('.');

                if (extenstion_delimiter == std::string::npos)
                {
                    m_logger << "----Warning: filename doesn't contain extension----\n";
                }
                else
                {
                    m_extension = m_filepath.substr(extenstion_delimiter + 1);
                }

                m_logger << "----Loading file SUCCESS----\n";
            }
            else
            {
                m_logger << "----Loading file ERROR----\n";
            }
        }
        m_ifstream().close();
        m_logger << "----Loading file: " << filepath << "----END\n";

        return result;
    }

    bool c_file::save_default(std::wstring_view filepath)
    {
        bool result = false;

        m_logger << "----Saving file to filepath: " << filepath << "----START\n";
        m_ofstream().open(filepath, std::ios::binary);
        {
            result = m_ofstream().good();

            if (result)
            {
                if (m_data_shared_ptr.use_count() > 0)
                {
                    m_ofstream().write
                    (reinterpret_cast<const char*>(m_data_shared_ptr->data()), m_data_shared_ptr->size());

                    if (m_ofstream().good())
                    {
                        m_state = enm_state::good;
                        result = true;
                    }
                }
                else
                {
                    m_logger << "----ERROR: data isn't initialized.----\n";
                }

            }
            else
            {
                m_logger << "----Opening file ERROR----\n";
            }
        }
        m_ofstream().close();

        if (result)
        {
            m_logger << "----Saving file SUCCESS----\n";
        }
        else
        {
            m_logger << "----Saving file ERROR----\n";
        }

        return result;
    }
}