#include "owd_filesystem_.h"
#include "../src/c_current_dir.h"
#include "../src/c_files_in_directory.h"

static auto static_current_dir = new owd_lib::c_current_dir();
static auto static_files_in_directory = new owd_lib::c_files_in_directory();

std::wstring_view owd::current_folder()
{
    return (*static_current_dir)();
}

std::vector<std::wstring>& owd::files_in_directory(std::wstring_view directory_path)
{
    return static_files_in_directory->files_in_directory(directory_path);
}

std::vector<std::wstring>& owd::folders_in_directory(std::wstring_view directory_path)
{
    return static_files_in_directory->folders_in_directory(directory_path);
}

std::vector<std::wstring>& owd::directory_contents(std::wstring_view directory_path)
{
    return static_files_in_directory->files_and_folders_in_directory(directory_path);
}
