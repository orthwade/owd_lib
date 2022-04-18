#include "owd_misc_.h"

namespace owd
{

    bool c_basic_object::good() const
    {
        return default_good();
    }
    bool c_basic_object::set_bad()
    {
        return m_good = false;
    }
    data_t& c_basic_object::data()
    {
        return m_data_shared_ptr;
    }
    byte_t* c_basic_object::data_raw_ptr()
    {
        return data()->data();
    }
    size_t c_basic_object::size_bytes() const
    {
        return m_data_shared_ptr->size();
    }
    c_basic_object::c_basic_object()
        :
        m_name(L"basic_object"),
        m_data_shared_ptr(std::make_shared<bytes_t>()),
        m_good(true),
        m_logger(L"basic_object_logger")
    {
    }
    void c_basic_object::reset()
    {
    }
    void c_basic_object::set_name(std::wstring_view name)
    {
        m_name = name;
    }
    std::wstring_view c_basic_object::name() const
    {
        return m_name;
    }
    bool c_basic_object::default_good() const
    {
        return m_good;
    }
}

