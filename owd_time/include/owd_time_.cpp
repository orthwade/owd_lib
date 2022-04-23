#include "owd_time_.h"
#include "../src/time_date.h"
#include "../src/c_sleep_for.h"
#include "../src/c_async_timer.h"
static auto set_time_resolution = timeBeginPeriod(1);

std::string owd::time_date()
{
    auto t_ = owd_lib::c_time_date();
    return t_.time_date();
}

std::string owd::time()
{
    auto t_ = owd_lib::c_time_date();
    return t_.time();
}

std::string owd::time_ms()
{
    auto t_ = owd_lib::c_time_date();
    return t_.time_ms();
}

std::string owd::date()
{
    auto t_ = owd_lib::c_time_date();
    return t_.date();
}

void owd::sleep_for_ms(size_t count)
{
#ifdef _WIN32
    Sleep(count);
#else

#endif // _WIN32
}

owd_lib::c_async_timer_lib* async_timer_lib(void* data)
{
    return reinterpret_cast<owd_lib::c_async_timer_lib*>(data);
}

void owd::c_async_timer::start(size_t period_mcs)
{
    //terminate();
    auto t_ = async_timer_lib(m_data);
    t_->start(period_mcs);
}

void owd::c_async_timer::wait()
{
    if (m_data != nullptr)
    {
        auto t_ = async_timer_lib(m_data);
        t_->wait();
    }
}

void owd::c_async_timer::stop()
{
    if (m_data != nullptr)
    {
        auto t_ = async_timer_lib(m_data);
        t_->stop();
    }
}

void owd::c_async_timer::terminate()
{
    if (m_data == nullptr)
    {

    }
    else
    {
        auto t_ = async_timer_lib(m_data);
        t_->terminate();
        delete async_timer_lib(m_data);
        m_data = nullptr;
    }
}

owd::c_async_timer::c_async_timer()
    :
    m_data(new owd_lib::c_async_timer_lib())
{
    auto t_ = async_timer_lib(m_data);
    t_->init();
}

owd::c_async_timer::~c_async_timer()
{
    terminate();
}

namespace owd
{
   
}

