#include "text_file_to_string.h"

static std::wifstream ifs{};


std::wstring owd_lib::text_file_to_wstring(std::wstring_view filepath)
{
	ifs.open(filepath.data());

	std::wstring content((std::istreambuf_iterator<wchar_t>(ifs)), (std::istreambuf_iterator<wchar_t>()));

	ifs.close();

	return content;
}

std::string owd_lib::text_file_to_string(std::wstring_view filepath)
{
	ifs.open(filepath.data());

	std::wstring content((std::istreambuf_iterator<wchar_t>(ifs)), (std::istreambuf_iterator<wchar_t>()));

	ifs.close();

	return c_convert_strings::utf_8(content);
}
