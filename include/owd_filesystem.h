#pragma once
#include <string_view>
#include <vector>

namespace owd
{
	std::wstring_view current_folder();

	std::vector<std::wstring>& files_in_directory	(std::wstring_view directory_path);
	std::vector<std::wstring>& folders_in_directory	(std::wstring_view directory_path);
	std::vector<std::wstring>& directory_contents	(std::wstring_view directory_path);

}