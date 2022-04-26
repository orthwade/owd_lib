#include "owd_filesystem_.h"
#include "../src/c_current_dir.h"
#include "../src/c_files_in_directory.h"

static auto static_current_dir = new owd_lib::c_current_dir();
static auto static_files_in_directory = new owd_lib::c_files_in_directory();

std::wstring_view owd::current_folder()
{
    if (static_current_dir == nullptr)
    {
        static_current_dir = new owd_lib::c_current_dir();
    }
    return (*static_current_dir)();
}

std::vector<std::wstring>& owd::files_in_directory(std::wstring_view directory_path)
{
    return static_files_in_directory->files_in_directory(directory_path);
}

std::vector<std::wstring>& owd::folders_in_directory(std::wstring_view directory_path)
{
    return static_files_in_directory->folders_in_directory(directory_path);
}

std::vector<std::wstring>& owd::directory_contents(std::wstring_view directory_path)
{
    return static_files_in_directory->files_and_folders_in_directory(directory_path);
}

namespace owd
{
	c_ifstream::c_ifstream()
	{
	}
	c_ifstream::~c_ifstream()
	{
	}
	c_ifstream::c_ifstream(const c_ifstream& other)
	{
	}
	c_ifstream& c_ifstream::operator=(const c_ifstream& other)
	{
		return *this;
	}

	c_ofstream::c_ofstream()
	{
	}
	c_ofstream::~c_ofstream()
	{
	}
	c_ofstream::c_ofstream(const c_ofstream& other)
	{
	}
	c_ofstream& c_ofstream::operator=(const c_ofstream& other)
	{
		return *this;
	}

	c_wifstream::c_wifstream()
	{
	}
	c_wifstream::~c_wifstream()
	{
	}
	c_wifstream::c_wifstream(const c_wifstream& other)
	{
	}
	c_wifstream& c_wifstream::operator=(const c_wifstream& other)
	{
		return *this;
	}

	c_wofstream::c_wofstream()
	{
	}
	c_wofstream::~c_wofstream()
	{
	}
	c_wofstream::c_wofstream(const c_wofstream& other)
	{
	}
	c_wofstream& c_wofstream::operator=(const c_wofstream& other)
	{
		return *this;
	}

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

    c_textfile::c_textfile()
    {
        m_logger.set_name(L"textfile_logger");
        set_name(L"textfile");
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
                m_utf_8.assign(std::istreambuf_iterator<char>(m_ifstream()), std::istreambuf_iterator<char>());
                m_unicode = unicode(m_utf_8);
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

        m_logger << "Writing to text file: " << filepath << '\n';

        m_ofstream().open(filepath);
        {
            result = m_ofstream().good();

            if (result)
            {
                m_ofstream() << m_utf_8;
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
    std::wstring_view c_textfile::view_unicode()
    {
        return m_unicode;
    }
    std::string_view c_textfile::view_utf_8()
    {
        return m_utf_8;
    }
    std::wstring_view c_textfile::view()
    {
        return m_unicode;
    }
}