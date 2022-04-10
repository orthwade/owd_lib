#include "owd_misc_.h"

namespace owd
{
    bool c_basic_object::good() const
    {
        return default_good();
    }
    c_basic_object::c_basic_object(std::wstring_view name)
        :
        m_name(name)
    {
    }
    c_basic_object::c_basic_object()
    {
    }
    void c_basic_object::reset()
    {
        *this = c_basic_object();
    }
}

