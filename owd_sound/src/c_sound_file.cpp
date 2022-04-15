#include "c_sound_file.h"

namespace owd_lib
{
    c_sound_file::c_sound_file(std::wstring_view name)
    {
        set_name(name);
        set_logger_name(L"sound_file_logger");
    }
    c_sound_file::c_sound_file()
        :
        c_sound_file(L"sound_file")
    {
    }
}

