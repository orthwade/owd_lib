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

}