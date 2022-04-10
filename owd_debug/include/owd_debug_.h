#pragma once
#include <string_view>

namespace owd
{
	class c_logger
	{
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="mode">
		/// 0: none
		/// 1: console
		/// 2: text file
		/// 3: console and text file</param>
		void set_mode(uint16_t mode);

		static void enable_global_mode_override();
		static void disable_global_mode_override();
		static void set_global_mode_override(uint16_t mode);

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
		c_logger& operator<<(const wchar_t* input);
		c_logger& operator<<(std::string_view input);
		c_logger& operator<<(std::wstring_view input);

		c_logger& operator<<(char c);
		c_logger& operator<<(wchar_t c);

		c_logger();
		c_logger(std::wstring_view name);
		c_logger(std::wstring_view name, uint16_t mode);

		~c_logger();

	private:
		std::wstring m_name;
		void* m_data;
	};
}