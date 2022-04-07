#include "compare_strings.h"

namespace owd_lib
{
	bool strings_are_equal(std::wstring_view one, std::wstring_view two)
	{
		auto int_ = wcscmp(one.data(), two.data());
		return (int_ == 0);
	}
}
