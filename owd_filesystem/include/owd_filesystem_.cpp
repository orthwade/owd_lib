#include "owd_filesystem_.h"
#include "../src/c_current_dir.h"

static owd_lib::c_current_dir static_current_dir{};

std::wstring_view owd::current_folder()
{
    return static_current_dir();
}
