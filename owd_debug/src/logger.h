#pragma once
#include <string_view>
#include <iostream>
#include <string>
#include <mutex>
#include <fstream>
#include <filesystem>

#include <io.h>
#include <fcntl.h>

#ifndef ASSERT
#define ASSERT(x) if(!(x)) __debugbreak();
#endif // !ASSERT

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

	class c_logger_lib
	{
	public:
		c_logger_lib();
		c_logger_lib(std::wstring_view name);
		c_logger_lib(std::wstring_view name, owd_lib::enm_log_mode mode);

		~c_logger_lib();

		c_logger_lib(const c_logger_lib& other);
		c_logger_lib& operator=(const c_logger_lib& other);

		void set_name(std::wstring_view name);

		std::wstring_view name()
		{
			return m_name;
		}
		
		c_logger_lib& operator<<(uint8_t  input);
		c_logger_lib& operator<<(uint16_t input);
		c_logger_lib& operator<<(uint32_t input);
		c_logger_lib& operator<<(uint64_t input);

		c_logger_lib& operator<<(int8_t  input);
		c_logger_lib& operator<<(int16_t input);
		c_logger_lib& operator<<(int32_t input);
		c_logger_lib& operator<<(int64_t input);

		c_logger_lib& operator<<(float  input);
		c_logger_lib& operator<<(double input);

		c_logger_lib& operator<<(const char* input);
		c_logger_lib& operator<<(std::string_view input);
		c_logger_lib& operator<<(std::wstring_view input);

		c_logger_lib& operator<<(char c);
		c_logger_lib& operator<<(wchar_t c);

		void set_mode(enm_log_mode mode);

		inline static void enable_global_mode_override() { log_mode_override_enabled = true; }
		inline static void disable_global_mode_override() { log_mode_override_enabled = false; }
		inline static void set_global_mode_override(enm_log_mode mode) { log_mode_override = mode; }

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
		
		std::wstring		m_curr_dir_str;

		std::wstring		m_logs_folder_path;

		std::wstring		m_common_log_file_path;
		std::wstring		m_log_file_path;

		std::wstring	m_time_date_str{};
		std::wstring	m_date_str{};
		std::wstring	m_date_buffer_str{};

		std::recursive_mutex m_mtx;

		std::wofstream m_common_ofstream_file;
		std::wofstream m_ofstream_file;

		//std::vector

	};
}
