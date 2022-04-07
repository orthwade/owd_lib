#include "c_current_dir.h"

namespace owd_lib
{
	c_current_dir::c_current_dir()
		: m_str(std::filesystem::current_path().wstring())
	{
	}

	c_current_dir::~c_current_dir()
	{
	}

	std::wstring_view c_current_dir::operator()()
	{
		return m_str;
	}
}


