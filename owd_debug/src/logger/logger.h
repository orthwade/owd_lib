#pragma once
#include <string_view>
#include <iostream>
#include <string>
#include <mutex>
#include <fstream>
#include <filesystem>

#include <io.h>
#include <fcntl.h>

//#ifdef _WIN32
//#include <Windows.h>
//#endif // _WIN32

//#include "../../misc/c_basic_object.h"

#define ASSERT(x) if(!(x)) __debugbreak();


//#ifndef OWD_LOGGER_MODE_OVERRIDE
//#define OWD_LOGGER_MODE_OVERRIDE
//#endif // OWD_LOGGER_MODE_OVERRIDE
//
//#ifdef OWD_LOGGER_MODE_OVERRIDE
//#define OWD_LOGGER_MODE_OVERRIDE_NONE 0
//#define OWD_LOGGER_MODE_OVERRIDE_CONSOLE 1
//#define OWD_LOGGER_MODE_OVERRIDE_FILE 2
//#define OWD_LOGGER_MODE_OVERRIDE_BOTH 3
//#endif // OWD_LOGGER_MODE_OVERRIDE

namespace owd_lib
{
	enum class enm_log_mode
	{
		none,
		console,
		file,
		both
	};

	enum class enm_log_mode_override
	{
		NO, YES
	};

	constexpr owd_lib::enm_log_mode default_log_mode = enm_log_mode::both;

	class c_logger
	{
	public:
		c_logger();
		c_logger(std::wstring_view name);
		c_logger(std::wstring_view name, owd_lib::enm_log_mode mode);

		~c_logger();

		c_logger(const c_logger& other);
		c_logger& operator=(const c_logger& other);

		void set_name(std::wstring_view name);

		std::wstring_view name()
		{
			return m_name;
		}
		
		c_logger& operator<<(uint8_t  input);
		c_logger& operator<<(uint16_t input);
		c_logger& operator<<(uint32_t input);
		c_logger& operator<<(uint64_t input);

		c_logger& operator<<(int8_t  input);
		c_logger& operator<<(int16_t input);
		c_logger& operator<<(int32_t input);
		c_logger& operator<<(int64_t input);

		c_logger& operator<<(float  input);
		c_logger& operator<<(double input);

		c_logger& operator<<(const char* input);
		c_logger& operator<<(std::string_view input);
		c_logger& operator<<(std::wstring_view input);

		c_logger& operator<<(char c);
		c_logger& operator<<(wchar_t c);

		void set_mode(enm_log_mode mode);
		bool global_override_mode();

		static bool log_mode_override_enabled;

		static enm_log_mode log_mode_override;

		static char const* const mode_c_str(enm_log_mode enm_mode);

	private:
		void m_print();

		enm_log_mode m_mode = default_log_mode;
		enm_log_mode m_mode_override = default_log_mode;

		std::wstring m_name{};
		std::wstring m_line{};
		
		owd_lib::c_current_dir m_curr_dir;
		std::wstring		m_curr_dir_str;

		std::wstring		m_logs_folder_path;

		std::wstring		m_common_log_file_path;
		std::wstring		m_log_file_path;

		c_time_date	    m_time_date{};
		std::wstring	m_time_date_str{};
		std::wstring	m_date_str{};
		std::wstring	m_date_buffer_str{};

		std::recursive_mutex m_mtx;

		std::wofstream m_common_ofstream_file;
		std::wofstream m_ofstream_file;

		//std::vector

	};
}
