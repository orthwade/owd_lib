#pragma once
#include <string>
#include <filesystem>

namespace owd_lib
{
	class c_current_dir
	{
	public:
		c_current_dir();
		~c_current_dir();

		std::wstring_view operator()();

	private:
		std::wstring m_str;
	};
}


