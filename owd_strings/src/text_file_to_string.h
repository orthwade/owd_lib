#pragma once
#include <string>
#include <fstream>
#include <istream>
#include <string_view>
#include "c_convert_strings.h"

namespace owd_lib
{
	std::wstring text_file_to_wstring(std::wstring_view filepath);
	std::string text_file_to_string(std::wstring_view filepath);
}