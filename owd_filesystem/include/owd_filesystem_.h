#pragma once
#include <string_view>
#include <vector>
#include <fstream>

#include <owd_debug.h>
#include <owd_misc.h>

namespace owd
{
	std::wstring_view current_folder();

	std::vector<std::wstring>& files_in_directory	(std::wstring_view directory_path);
	std::vector<std::wstring>& folders_in_directory	(std::wstring_view directory_path);
	std::vector<std::wstring>& directory_contents	(std::wstring_view directory_path);

	class c_ifstream
	{
	public:
		c_ifstream();
		~c_ifstream();

		c_ifstream(const c_ifstream& other);
		c_ifstream& operator=(const c_ifstream& other);

		inline std::ifstream& operator()() { return m_ifstream; }

	private:
		std::ifstream m_ifstream{};
	};

	class c_ofstream
	{
	public:
		c_ofstream();
		~c_ofstream();

		c_ofstream(const c_ofstream& other);
		c_ofstream& operator=(const c_ofstream& other);

		inline std::ofstream& operator()() { return m_ofstream; }

	private:
		std::ofstream m_ofstream{};
	};

	class c_wifstream
	{
	public:
		c_wifstream();
		~c_wifstream();

		c_wifstream(const c_wifstream& other);
		c_wifstream& operator=(const c_wifstream& other);

		inline std::wifstream& operator()() { return m_wifstream; }

	private:
		std::wifstream m_wifstream{};
	};

	class c_wofstream
	{
	public:
		c_wofstream();
		~c_wofstream();

		c_wofstream(const c_wofstream& other);
		c_wofstream& operator=(const c_wofstream& other);

		inline std::wofstream& operator()() { return m_wofstream; }

	private:
		std::wofstream m_wofstream{};
	};

	class c_file : public c_basic_object
	{
	public:
		enum class enm_state
		{
			not_loaded,
			good,
			error
		};

		c_file();

		virtual bool load(std::wstring_view filepath);
		virtual bool load(std::wstring_view filepath, std::wstring_view name);

		virtual bool save(std::wstring_view filepath);

		virtual void reset() override;

		inline std::wstring_view filepath() const { return m_filepath; }

		inline enm_state state() const { return m_state; }

		bool good() const override;

		std::wstring_view filepath();
	
	protected:
		c_logger m_logger{ L"file_logger" };

		enm_state		m_state = enm_state::not_loaded;

		std::wstring	m_extension{ L"owd_file" };
		std::wstring	m_filepath{};

		c_ifstream	m_ifstream{};

		c_ofstream	m_ofstream{};

	private:
		bool load_default(std::wstring_view filepath);
		bool load_default(std::wstring_view filepath, std::wstring_view name);
		bool save_default(std::wstring_view filepath);
	};

	class c_textfile : public c_file
	{
	public:
		c_textfile();

		bool load(std::wstring_view filepath) override;
		bool load(std::wstring_view filepath, std::wstring_view name) override;

		bool save(std::wstring_view filepath) override;

		std::wstring_view view_unicode();
		std::string_view view_utf_8();
		std::wstring_view view();

	private:
		std::string m_utf_8{};
		std::wstring m_unicode{};

	};

    template <class T>
    class c_file_bank : public c_object_bank<T>
    {
    public:
        c_file_bank();
        c_file_bank(std::wstring_view name);

        ~c_file_bank();

        bool load(std::wstring_view filepath);
        bool load(std::wstring_view filepath, std::wstring_view name);

        std::shared_ptr<T>& load_and_get(std::wstring_view filepath);

        std::shared_ptr<T>& by_filepath(std::wstring_view filepath);

        void erase_by_filepath(std::wstring_view filepath);
        void erase_by_name(std::wstring_view name);

    protected:

    };

    template<class T>
    c_file_bank<T>::c_file_bank()
    {
    }

    template<class T>
    c_file_bank<T>::c_file_bank(std::wstring_view name)
    {
    }

    template<class T>
    c_file_bank<T>::~c_file_bank()
    {
    }

    template<class T>
    bool c_file_bank<T>::load(std::wstring_view filepath)
    {
        return load(filepath, filepath);
    }

    template<class T>
    bool c_file_bank<T>::load(std::wstring_view filepath, std::wstring_view name)
    {
        bool result = false;

        auto file = std::make_shared<T>();
        this->m_logger << "----Loading file; filepath: " << filepath << "----\n";
        {
            if (this->m_vec_objects.empty())
            {

            }
            else
            {
                for (uint64_t i = 0; i != this->m_vec_objects.size(); ++i)
                {
                    if (strings_are_equal(this->m_vec_objects[i]->filepath(), filepath))
                    {
                        this->m_logger << "The filepath is already in the bank\n";
                        this->m_logger << "Loading ABORTED\n";

                        return false;
                    }
                    if (strings_are_equal(this->m_vec_objects[i]->name(), name))
                    {
                        this->m_logger << "The name is already in the bank\n";
                        this->m_logger << "Loading ABORTED\n";

                        return false;
                    }
                }
            }

            result = file->load(filepath, name);

            if (result)
            {
                this->m_vec_objects.push_back(file);
                this->m_logger << "Loading SUCCESS\n";
            }
            else
            {
                this->m_logger << "Loading ERROR\n";
            }
        }
        this->m_logger << "----Loading file END----\n";

        return result;
    }

    template<class T>
    std::shared_ptr<T>& c_file_bank<T>::load_and_get(std::wstring_view filepath)
    {
        auto file = std::make_shared<T>();
        this->m_logger << "----Loading file; filepath: " << filepath << "----\n";
        {
            if (this->m_vec_objects.empty())
            {

            }
            else
            {
                for (uint64_t i = 0; i != this->m_vec_objects.size(); ++i)
                {
                    if (strings_are_equal(this->m_vec_objects[i]->filepath(), filepath))
                    {
                        this->m_logger << "The filepath is already in the bank\n";
                        this->m_logger << "Loading ABORTED\n";

                        return this->m_vec_objects[i];
                    }
                }
            }

            if (file->load(filepath))
            {
                this->m_vec_objects.push_back(file);
                this->m_logger << "Loading SUCCESS\n";
                return this->m_vec_objects.back();
            }
            else
            {
                this->m_logger << "Loading ERROR\n";
            }
        }
        this->m_logger << "----Loading file END----\n";

        return file;
    }


    template<class T>
    std::shared_ptr<T>& c_file_bank<T>::by_filepath(std::wstring_view filepath)
    {
        auto file = std::make_shared<T>();

        this->m_logger << "----Getting file by filepath: " << filepath << " START----\n";
        {
            if (this->m_vec_objects.empty())
            {
                this->m_logger << "ERROR: bank is empty\n";
            }
            else
            {
                bool found = false;
                for (uint64_t i = 0; i != this->m_vec_objects.size(); ++i)
                {
                    if (strings_are_equal(this->m_vec_objects[i]->filepath(), filepath))
                    {
                        file = this->m_vec_objects[i];
                        found = true;
                    }
                }
                if (found)
                {
                    this->m_logger << "file found\n";
                }
                else
                {
                    this->m_logger << "file NOT found\n";
                }
            }
        }
        this->m_logger << "----Getting file END----\n";

        return file;
    }
    template<class T>
    void c_file_bank<T>::erase_by_filepath(std::wstring_view filepath)
    {
        this->m_logger << "----Erasing object by filepath: " << filepath << "----\n";
        {
            if (this->m_vec_objects.empty())
            {
                this->m_logger << "ERROR: bank is empty\n";
            }
            else
            {
                auto iter = this->m_vec_objects.begin();

                uint64_t index = 0;

                bool found = false;

                for (uint64_t i = 0; i != this->m_vec_objects.size(); ++i, ++index)
                {
                    if (strings_are_equal(this->m_vec_objects[i]->filepath(), filepath))
                    {
                        found = true;
                        break;
                    }

                }
                if (found)
                {
                    this->m_logger << "object found\n";
                }
                else
                {
                    this->m_logger << "object NOT found\n";
                }

                iter += index;

                this->m_vec_objects.erase(iter);

                this->m_logger << "----Erasing object OK----\n";
            }
        }
        this->m_logger << "----Erasing object END----\n";
    }

    template<class T>
    void c_file_bank<T>::erase_by_name(std::wstring_view name)
    {
        this->m_logger << "----Erasing object by name: " << name << "----\n";
        {
            if (this->m_vec_objects.empty())
            {
                this->m_logger << "ERROR: bank is empty\n";
            }
            else
            {
                auto iter = this->m_vec_objects.begin();

                uint64_t index = 0;

                bool found = false;

                for (uint64_t i = 0; i != this->m_vec_objects.size(); ++i, ++index)
                {
                    if (strings_are_equal(this->m_vec_objects[i]->name(), name))
                    {
                        found = true;
                        break;
                    }

                }
                if (found)
                {
                    this->m_logger << "object found\n";
                }
                else
                {
                    this->m_logger << "object NOT found\n";
                }

                iter += index;

                this->m_vec_objects.erase(iter);

                this->m_logger << "----Erasing object OK----\n";
            }
        }
        this->m_logger << "----Erasing object END----\n";
    }


}