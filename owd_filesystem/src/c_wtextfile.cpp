#include "c_wtextfile.h"

namespace owd_lib
{
    c_wtextfile::c_wtextfile()
    {
        set_name(L"wtextfile");
        set_logger_name(L"wtextfile_logger");
    }
    bool c_wtextfile::load(std::wstring_view filepath)
    {
        return load(filepath, filepath);
    }
    bool c_wtextfile::load(std::wstring_view filepath, std::wstring_view name)
    {
        bool result = false;
        set_name(name);
        m_logger << "----Loading text file: " << filepath << "----START\n";
        m_logger << "file name: " << name << '\n';
        m_wifstream().open(filepath);
        {
            result = m_wifstream().good();

            if (result)
            {
                m_text.assign(std::istreambuf_iterator<wchar_t>(m_wifstream()), std::istreambuf_iterator<wchar_t>());
                m_state = enm_state::good;
                m_logger << "----Loading file SUCCESS----\n";
            }
            else
            {
                m_state = enm_state::error;
                m_logger << "----Loading file ERROR----\n";
            }
        }
        m_wifstream().close();

        return result;
    }
    bool c_wtextfile::save(std::wstring_view filepath)
    {
        bool result = false;

        m_logger << "Writing to text file: " << filepath << '\n';

        m_wofstream().open(filepath);
        {
            result = m_wofstream().good();

            if (result)
            {
                m_wofstream() << m_text;
            }

        }
        m_wofstream().close();
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

