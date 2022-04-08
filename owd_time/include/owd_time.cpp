#include "owd_time.h"
#include "../src/time_date.h"
#include "../src/c_sleep_for.h"
#include "../src/c_async_timer.h"

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
    owd_lib::c_sleep_for_ms s_{};
    s_(count);
}

owd_lib::c_async_timer_lib* async_timer_lib(void* data)
{
    return reinterpret_cast<owd_lib::c_async_timer_lib*>(data);
}

void owd::c_async_timer::start(size_t period_ms)
{
    terminate();
    m_data = new owd_lib::c_async_timer_lib();
    auto t_ = async_timer_lib(m_data);
    t_->init(period_ms);
    t_->start();
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
        delete m_data;
        m_data = nullptr;
    }
}

owd::c_async_timer::c_async_timer()
    :
    m_data(nullptr)
{
}

owd::c_async_timer::~c_async_timer()
{
    terminate();
}
