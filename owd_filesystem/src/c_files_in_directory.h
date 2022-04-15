#pragma once
#include <filesystem>

namespace owd_lib
{
	class c_files_in_directory
	{
	public:
		c_files_in_directory();
		~c_files_in_directory();
		std::vector<std::wstring>& operator()(std::wstring_view directory_path);
	private:
		std::vector<std::wstring> m_vec{};
	};
}