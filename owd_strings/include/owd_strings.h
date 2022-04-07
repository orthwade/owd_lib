#pragma once
#include <string_view>

namespace owd
{
	bool strings_are_equal(std::wstring_view first, std::wstring_view second);

	std::wstring text_file_to_wstring(std::wstring_view filepath);
	std::string  text_file_to_string (std::wstring_view filepath);

	std::wstring unicode(const char* utf_8_in);
	std::string  utf_8  (const wchar_t* unicode_in);

	std::wstring unicode(const std::string_view  utf_8_in);
	std::string  utf_8  (const std::wstring_view unicode_in);
}