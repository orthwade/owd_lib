#pragma once
#include <filesystem>

namespace owd_lib
{
	class c_files_in_directory
	{
	public:
		c_files_in_directory();
		~c_files_in_directory();

		std::vector<std::wstring>& files_in_directory				(std::wstring_view directory_path);
		std::vector<std::wstring>& folders_in_directory				(std::wstring_view directory_path);
		std::vector<std::wstring>& files_and_folders_in_directory	(std::wstring_view directory_path);

	private:
		std::vector<std::wstring> m_vec_files_in_directory{};
		std::vector<std::wstring> m_vec_folders_in_directory{};
		std::vector<std::wstring> m_vec_files_and_folders_in_directory{};
	};
}