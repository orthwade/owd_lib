#include "c_textfile.h"

namespace owd_lib
{
    c_textfile::c_textfile()
    {
        set_name(L"textfile");
        set_logger_name(L"textfile_logger");
    }
    bool c_textfile::load(std::wstring_view filepath)
    {
        return load(filepath, filepath);
    }
    bool c_textfile::load(std::wstring_view filepath, std::wstring_view name)
    {
        bool result = false;
        set_name(name);
        m_logger << "----Loading text file: " << filepath << "----START\n";
        m_logger << "file name: " << name << '\n';
        m_ifstream().open(filepath);
        {
            result = m_ifstream().good();

            if (result)
            {
                m_text.assign(std::istreambuf_iterator<char>(m_ifstream()), std::istreambuf_iterator<char>());
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

        return result;
    }
    bool c_textfile::save(std::wstring_view filepath)
    {
        bool result = false;

        m_logger << "Writing to text file: " <<  filepath << '\n';
        
        m_ofstream().open(filepath);
        {
            result = m_ofstream().good();

            if (result)
            {
                m_ofstream() << m_text;
            }

        }
        m_ofstream().close();
        if (result)
        {
            m_logger << "----Writing file SUCCESS----\n";
        }
        else
        {
            m_logger << "----Writing file ERROR----\n";
        }
        return result;
    }
}

