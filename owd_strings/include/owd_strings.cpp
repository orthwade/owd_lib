#include "owd_strings.h"
#include "../src/compare_strings.h"
#include "../src/c_convert_strings.h"
#include "../src/text_file_to_string.h"

bool owd::strings_are_equal(std::wstring_view first, std::wstring_view second)
{
    return owd_lib::strings_are_equal(first, second);
}

std::wstring owd::text_file_to_wstring(std::wstring_view filepath)
{
    return owd_lib::text_file_to_wstring(filepath);
}

std::string owd::text_file_to_string(std::wstring_view filepath)
{
    return owd_lib::text_file_to_string(filepath);
}

std::wstring owd::unicode(const char* utf_8_in)
{
    return owd_lib::c_convert_strings::unicode(utf_8_in);
}

std::string owd::utf_8(const wchar_t* unicode_in)
{
    return owd_lib::c_convert_strings::utf_8(unicode_in);
}

std::wstring owd::unicode(const std::string_view utf_8_in)
{
    return owd_lib::c_convert_strings::unicode(utf_8_in);
}

std::string owd::utf_8(const std::wstring_view unicode_in)
{
    return owd_lib::c_convert_strings::utf_8(unicode_in);
}
