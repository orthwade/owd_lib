#include "logger.h"
#include <owd_strings.h>
#include <owd_time.h>
#include <owd_filesystem.h>

namespace owd_lib
{
    static auto setmode_result = _setmode(_fileno(stdout), _O_WTEXT);

    bool c_logger_lib::log_mode_override_enabled = true;
    enm_log_mode c_logger_lib::log_mode_override = enm_log_mode::none;

    c_logger_lib::c_logger_lib()
        :
        m_curr_dir_str(owd::current_folder()),
        m_logs_folder_path(m_curr_dir_str + L"/output/logs/"),
        m_time_date_str(owd::unicode(owd::time_date())),
        m_date_str(m_time_date_str.substr(0, 10))
        //m_log_file_path(m_logs_folder_path + m_date_str + L'/' + m_name + L".txt"),
        //m_common_log_file_path(m_logs_folder_path + m_date_str + L"/common_log.txt")
    {
        set_mode(m_mode);
        //m_date_str = (m_time_date_str.substr(0, 9));
        m_log_file_path = (m_logs_folder_path + m_date_str + L'/' + m_name + L".txt");
        m_common_log_file_path = (m_logs_folder_path + m_date_str + L"/common_log.txt");

        std::filesystem::create_directory(L"output");
        std::filesystem::create_directory(L"output/logs");
        std::filesystem::create_directory(std::wstring(L"output/logs/") + m_date_str);
    }

    c_logger_lib::c_logger_lib(std::wstring_view name)
        :
        m_name(name),
        m_curr_dir_str(owd::current_folder()),
        m_logs_folder_path(m_curr_dir_str + L"/output/logs/"),
        m_time_date_str(owd::unicode(owd::time_date())),
        m_date_str(m_time_date_str.substr(0, 10))
        //m_log_file_path(m_logs_folder_path + m_date_str + L'/' + m_name + L".txt"),
        //m_common_log_file_path(m_logs_folder_path + m_date_str + L"/common_log.txt")
    {
        set_mode(m_mode);
        //m_date_str = (m_time_date_str.substr(0, 9));
        m_log_file_path = (m_logs_folder_path + m_date_str + L'/' + m_name + L".txt");
        m_common_log_file_path = (m_logs_folder_path + m_date_str + L"/common_log.txt");

        std::filesystem::create_directory(L"output");
        std::filesystem::create_directory(L"output/logs");
        std::filesystem::create_directory(std::wstring(L"output/logs/") + m_date_str);
    }

    c_logger_lib::c_logger_lib(std::wstring_view name, owd_lib::enm_log_mode mode)
        :
        m_name(name),
        //m_mode(mode),
        m_curr_dir_str(owd::current_folder()),
        m_logs_folder_path(m_curr_dir_str + L"/output/logs/"),
        m_time_date_str(owd::unicode(owd::time_date())),
        m_date_str(m_time_date_str.substr(0, 10))
        //m_log_file_path(m_logs_folder_path + m_date_str + L'/' + m_name + L".txt"),
        //m_common_log_file_path(m_logs_folder_path + m_date_str + L"/common_log.txt")
    {
        set_mode(mode);
        //m_date_str = (m_time_date_str.substr(0, 9));
        m_log_file_path = (m_logs_folder_path + m_date_str + L'/' + m_name + L".txt");
        m_common_log_file_path = (m_logs_folder_path + m_date_str + L"/common_log.txt");

        std::filesystem::create_directory(L"output");
        std::filesystem::create_directory(L"output/logs");
        std::filesystem::create_directory(std::wstring(L"output/logs/") + m_date_str);
    }

    c_logger_lib::~c_logger_lib()
    {
    }

    c_logger_lib::c_logger_lib(const c_logger_lib& other)
    {
        *this = other;
    }

    c_logger_lib& c_logger_lib::operator=(const c_logger_lib& other)
    {
        if (this != &other)
        {
            //m_mode                  = other.m_mode;
            set_mode(other.m_mode);
            m_name                  = other.m_name;
            m_line                  = other.m_line;
            m_curr_dir_str          = other.m_curr_dir_str;
            m_logs_folder_path      = other.m_logs_folder_path;
            m_common_log_file_path  = other.m_common_log_file_path;
            m_log_file_path         = other.m_log_file_path;
            m_time_date_str         = other.m_time_date_str  ;   
            m_date_str              = other.m_date_str       ;   
            m_date_buffer_str       = other.m_date_buffer_str;   
            //m_common_ofstream_file  = other.m_common_ofstream_file;
            //m_ofstream_file         = other.m_ofstream_file   ;    
        }

        return *this;
    }

    void c_logger_lib::set_name(std::wstring_view name)
    {
        m_name = name;
    }

    c_logger_lib& c_logger_lib::operator<<(uint8_t input)
    {
        auto mode = m_mode;

        m_mtx.lock();
        {
            if (global_override_mode())
            {
                mode = log_mode_override;
            }
        }
        m_mtx.unlock();

        if (mode != enm_log_mode::none)
        {
            //std::wstring string_buffer = std::to_wstring(input);
            m_line.append(std::to_wstring(input));
        }

        return *this;
    }

    c_logger_lib& c_logger_lib::operator<<(uint16_t input)
    {
        auto mode = m_mode;

        m_mtx.lock();
        {
            if (global_override_mode())
            {
                mode = log_mode_override;
            }
        }
        m_mtx.unlock();

        if (mode != enm_log_mode::none)
        {
            //std::wstring string_buffer = std::to_wstring(input);
            m_line.append(std::to_wstring(input));
        }

        return *this;
    }

    c_logger_lib& c_logger_lib::operator<<(uint32_t input)
    {
        auto mode = m_mode;

        m_mtx.lock();
        {
            if (global_override_mode())
            {
                mode = log_mode_override;
            }
        }
        m_mtx.unlock();

        if (mode != enm_log_mode::none)
        {
            //std::wstring string_buffer = std::to_wstring(input);
            m_line.append(std::to_wstring(input));
        }

        return *this;
    }

    c_logger_lib& c_logger_lib::operator<<(uint64_t input)
    {
        auto mode = m_mode;

        m_mtx.lock();
        {
            if (global_override_mode())
            {
                mode = log_mode_override;
            }
        }
        m_mtx.unlock();

        if (mode != enm_log_mode::none)
        {
            //std::wstring string_buffer = std::to_wstring(input);
            m_line.append(std::to_wstring(input));
        }

        return *this;
    }

    c_logger_lib& c_logger_lib::operator<<(int8_t input)
    {
        auto mode = m_mode;

        m_mtx.lock();
        {
            if (global_override_mode())
            {
                mode = log_mode_override;
            }
        }
        m_mtx.unlock();

        if (mode != enm_log_mode::none)
        {
            //std::wstring string_buffer = std::to_wstring(input);
            m_line.append(std::to_wstring(input));
        }

        return *this;
    }

    c_logger_lib& c_logger_lib::operator<<(int16_t input)
    {
        auto mode = m_mode;
        m_mtx.lock();
        {
            if (global_override_mode())
            {
                mode = log_mode_override;
            }
        }
        m_mtx.unlock();

        if (mode != enm_log_mode::none)
        {
            //std::wstring string_buffer = std::to_wstring(input);
            m_line.append(std::to_wstring(input));
        }

        return *this;
    }

    c_logger_lib& c_logger_lib::operator<<(int32_t input)
    {
        auto mode = m_mode;
        m_mtx.lock();
        {
            if (global_override_mode())
            {
                mode = log_mode_override;
            }
        }
        m_mtx.unlock();

        if (mode != enm_log_mode::none)
        {
            //std::wstring string_buffer = std::to_wstring(input);
            m_line.append(std::to_wstring(input));
        }

        return *this;
    }

    c_logger_lib& c_logger_lib::operator<<(int64_t input)
    {
        auto mode = m_mode;
        m_mtx.lock();
        {
            if (global_override_mode())
            {
                mode = log_mode_override;
            }
        }
        m_mtx.unlock();

        if (mode != enm_log_mode::none)
        {
            //std::wstring string_buffer = std::to_wstring(input);
            m_line.append(std::to_wstring(input));
        }
        
        return *this;
    }

    c_logger_lib& c_logger_lib::operator<<(float input)
    {
        auto mode = m_mode;
        m_mtx.lock();
        {
            if (global_override_mode())
            {
                mode = log_mode_override;
            }
        }
        m_mtx.unlock();

        if (mode != enm_log_mode::none)
        {
            //std::wstring string_buffer = std::to_wstring(input);
            m_line.append(std::to_wstring(input));
        }

        return *this;
    }

    c_logger_lib& c_logger_lib::operator<<(double input)
    {
        auto mode = m_mode;
        m_mtx.lock();
        {
            if (global_override_mode())
            {
                m_mode = log_mode_override;
            }
        }
        m_mtx.unlock();

        if (m_mode != enm_log_mode::none)
        {
            //std::wstring string_buffer = std::to_wstring(input);
            m_line.append(std::to_wstring(input));
        }
        
        return *this;
    }

    c_logger_lib& c_logger_lib::operator<<(const char* input)
    {
        auto mode = m_mode;
        m_mtx.lock();
        {
            if (global_override_mode())
            {
                mode = log_mode_override;
            }
        }
        m_mtx.unlock();

        if (mode != enm_log_mode::none)
        {
            // "----Getting instance START----\n"
            //std::string string_buffer(input);

            std::wstring wstring_buffer = owd::unicode(input);

            //std::wstring wstring_buffer = std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>{}.from_bytes(string_buffer);

            //c_convert_strings::utf_8_to_unicode(string_buffer, wstring_buffer);

            if (wstring_buffer == L"")
            {
                return *this;
            }
            

            uint64_t last_index = wstring_buffer.size() - 1;

            m_line.append(wstring_buffer);

            if (wstring_buffer.at(last_index) == '\n')
            {
                m_line.pop_back();
                m_print();
            }
        }
        return *this;
    }

    c_logger_lib& c_logger_lib::operator<<(std::string_view input)
    {
        auto mode = m_mode;
        m_mtx.lock();
        {
            if (global_override_mode())
            {
                mode = log_mode_override;
            }
        }
        m_mtx.unlock();

        if (mode != enm_log_mode::none)
        {
            //std::string string_buffer(input);

            std::wstring wstring_buffer = owd::unicode(input);

            //c_convert_strings::utf_8_to_unicode(string_buffer, wstring_buffer);

            if (wstring_buffer == L"")
            {
                return *this;
            }

            uint64_t last_index = wstring_buffer.size() - 1;

            m_line.append(wstring_buffer);

            if (wstring_buffer.at(last_index) == '\n')
            {
                m_line.pop_back();
                m_print();
            }
        }
        return *this;
    }

    c_logger_lib& c_logger_lib::operator<<(std::wstring_view input)
    {
        auto mode = m_mode;
        m_mtx.lock();
        {
            if (global_override_mode())
            {
                mode = log_mode_override;
            }
        }
        m_mtx.unlock();

        if (mode != enm_log_mode::none)
        {
            std::wstring string_buffer = std::wstring(input);

            if (string_buffer == L"")
            {
                return *this;
            }

            uint64_t last_index = string_buffer.size() - 1;
            
            m_line.append(string_buffer);

            if (string_buffer.at(last_index) == '\n')
            {
                m_line.pop_back();
                m_print();
            }
        }
        return *this;
    }

    c_logger_lib& c_logger_lib::operator<<(char c)
    {
        auto mode = m_mode;
        m_mtx.lock();
        {
            if (global_override_mode())
            {
                mode = log_mode_override;
            }
        }
        m_mtx.unlock();

        if (mode != enm_log_mode::none)
        {
            if (c == '\n')
            {
                m_print();
            }
            else
            {
                m_line.push_back(c);
            }
        }

        return *this;
    }

    c_logger_lib& c_logger_lib::operator<<(wchar_t c)
    {
        auto mode = m_mode;
        
        m_mtx.lock();
        {
            if (global_override_mode())
            {
                mode = log_mode_override;
            }
        }
        m_mtx.unlock();
        if (mode != enm_log_mode::none)
        {
            if (c == '\n')
            {
                m_print();
            }
            else
            {
                m_line.push_back(c);
            }
        }

        return *this;
    }

    void c_logger_lib::set_mode(enm_log_mode mode)
    {
        if (global_override_mode())
        {
            //m_mode = log_mode_override;
        }
        else
        {
        }
        m_mode = mode;
    }

    bool c_logger_lib::global_override_mode()
    {
        return (log_mode_override_enabled);
    }

    char const* const c_logger_lib::mode_c_str(enm_log_mode enm_mode)
    {
        char const* const f[4] = {};
        auto ff = f;
        if (enm_mode == enm_log_mode::both)
        {
            return "console_and_file";
        }
        else if (enm_mode == enm_log_mode::console)
        {
            return "console";
        }
        else if (enm_mode == enm_log_mode::file)
        {
            return "file";
        }
        else if (enm_mode == enm_log_mode::none)
        {
            return "none";
        }
        return nullptr;
    }
    void c_logger_lib::m_print()
    {
        m_mtx.lock();
        {
            auto mode = m_mode;
            if (global_override_mode())
            {
                mode = log_mode_override;
            }
            else
            {

            }

            if (mode != enm_log_mode::none)
            {
                m_time_date_str.clear();
                m_time_date_str = owd::unicode(owd::time_date());

                //time_date_str.pop_back();
                m_line =
                   L"[" + m_time_date_str + L"] [" + m_name + L"] " + m_line;
                if (mode == enm_log_mode::console)
                {
                    std::wcout << m_line << '\n';
                }
                else if (mode == enm_log_mode::file)
                {
                    //m_date_buffer_str.clear();
                    //m_date_buffer_str.resize(10);
                    //memcpy(m_date_buffer_str.data(), m_time_date_str.data(), 10);
                    m_date_buffer_str = m_time_date_str.substr(0, 10);

                    if (m_date_buffer_str != m_date_str)
                    {
                        m_date_str = m_date_buffer_str;
                        std::filesystem::create_directory(std::wstring(L"output/logs/") + m_date_str);

                        m_log_file_path = m_logs_folder_path + m_date_str + L'/' + m_name + L".txt";

                        m_common_log_file_path = m_logs_folder_path + m_date_str + L"/common_log.txt";
                    }

                    m_common_ofstream_file.open(m_common_log_file_path.c_str(), std::ios_base::app);
                    m_common_ofstream_file << m_line << '\n';
                    m_common_ofstream_file.close();

                    m_ofstream_file.open(m_log_file_path.c_str(), std::ios_base::app);
                    m_ofstream_file << m_line << '\n';
                    m_ofstream_file.close();

                }
                else if (mode == enm_log_mode::both)
                {
                    std::wcout << m_line << '\n';

                    //m_date_buffer_str.clear();
                    //m_date_buffer_str.resize(10);
                    //memcpy(m_date_buffer_str.data(), m_time_date_str.data(), 10);
                    m_date_buffer_str = m_time_date_str.substr(0, 10);

                    if (m_date_buffer_str != m_date_str)
                    {
                        m_date_str = m_date_buffer_str;
                        std::filesystem::create_directory(std::wstring(L"output/logs/") + m_date_str);

                        m_log_file_path = m_logs_folder_path + m_date_str + L'/' + m_name + L".txt";

                        m_common_log_file_path = m_logs_folder_path + m_date_str + L"/common_log.txt";
                    }

                    m_common_ofstream_file.open(m_common_log_file_path.c_str(), std::ios_base::app);
                    m_common_ofstream_file << m_line << '\n';
                    m_common_ofstream_file.close();

                    m_ofstream_file.open(m_log_file_path.c_str(), std::ios_base::app);
                    m_ofstream_file << m_line << '\n';
                    m_ofstream_file.close();

                }
                m_line.clear();
            }
        }
        m_mtx.unlock();
    }
}
