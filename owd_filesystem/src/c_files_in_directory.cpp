#include "c_files_in_directory.h"

namespace owd_lib
{
	c_files_in_directory::c_files_in_directory()
	{
	}
	c_files_in_directory::~c_files_in_directory()
	{
	}
	std::vector<std::wstring>& c_files_in_directory::operator()(std::wstring_view directory_path)
	{
		m_vec.clear();
		for (const auto& file : std::filesystem::directory_iterator(directory_path))
		{
			m_vec.push_back(file.path());
		}
		return m_vec;
	}
}

