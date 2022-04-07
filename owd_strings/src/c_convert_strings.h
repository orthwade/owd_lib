#pragma once
#include <codecvt>

namespace owd_lib
{
	class c_convert_strings
	{
	public:
		static std::wstring unicode(const char*    utf_8_in);
		static std::string  utf_8  (const wchar_t* unicode_in);

		static std::wstring unicode(const std::string_view  utf_8_in);
		static std::string  utf_8  (const std::wstring_view unicode_in);

	private:
		c_convert_strings();
		~c_convert_strings();

		static c_convert_strings* m_singleton;

		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> m_converter{};
	};
}