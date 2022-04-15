#include "c_files_in_directory.h"

namespace owd_lib
{
	c_files_in_directory::c_files_in_directory()
	{
	}
	c_files_in_directory::~c_files_in_directory()
	{
	}
	std::vector<std::wstring>& c_files_in_directory::files_in_directory(std::wstring_view directory_path)
	{
		m_vec_files_in_directory.clear();
		for (const auto& unit : std::filesystem::directory_iterator(directory_path))
		{
			if (!unit.is_directory())
			{
				m_vec_files_in_directory.push_back(unit.path());
			}
		}
		return m_vec_files_in_directory;
	}
	std::vector<std::wstring>& c_files_in_directory::folders_in_directory(std::wstring_view directory_path)
	{
		m_vec_folders_in_directory.clear();
		for (const auto& unit : std::filesystem::directory_iterator(directory_path))
		{
			if (unit.is_directory())
			{
				m_vec_folders_in_directory.push_back(unit.path());
			}
		}
		return m_vec_folders_in_directory;
	}
	std::vector<std::wstring>& c_files_in_directory::files_and_folders_in_directory(std::wstring_view directory_path)
	{
		m_vec_files_and_folders_in_directory.clear();
		for (const auto& unit : std::filesystem::directory_iterator(directory_path))
		{
			m_vec_files_and_folders_in_directory.push_back(unit.path());
		}
		return m_vec_files_and_folders_in_directory;
	}
}

