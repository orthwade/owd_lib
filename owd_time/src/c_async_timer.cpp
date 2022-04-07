#include "c_async_timer.h"

namespace owd_lib
{
    c_async_timer::c_async_timer()
    {
    }
    c_async_timer::c_async_timer(uint64_t period_mcs)
    {
        //init(period_mcs);
        set_period(period_mcs);
    }
    c_async_timer::~c_async_timer()
    {
        terminate();
    }
    void c_async_timer::init()
    {
        terminate();
        m_thread_exists = true;
        m_thread() = std::thread(&c_async_timer::do_, this);
    }
    void c_async_timer::init(uint64_t period_mcs)
    {
        terminate();
        m_thread_exists = true;
        set_period(period_mcs);
        m_thread() = std::thread(&c_async_timer::do_, this);
    }
    void c_async_timer::terminate()
    {
        m_thread_exists = false;
        if (m_thread().joinable())
        {
            m_thread().join();
        }
    }
    void c_async_timer::start(uint64_t period_mcs)
    {
        set_period(period_mcs);
        m_state = enm_state::waiting;
    }
    void c_async_timer::start()
    {
        m_state = enm_state::waiting;
    }
    void c_async_timer::do_()
    {
        while (m_thread_exists)
        {

            if (m_state == enm_state::waiting)
            {
                m_frame_start_time = std::chrono::high_resolution_clock::now();
                while (true)
                {
                    m_frame_duration_int_mcs =
                        std::chrono::duration_cast<std::chrono::microseconds>
                        (std::chrono::high_resolution_clock::now() - m_frame_start_time).count();

                    if (m_frame_duration_int_mcs >= m_period_mcs)
                    {
                        m_state = enm_state::done;
                        break;
                    }
                }
            }
        }
    }
    void c_async_timer::wait()
    {
        while (m_state == enm_state::waiting)
        {

        }
    }
    void c_async_timer::stop()
    {
        m_state = enm_state::done;
    }
    void c_async_timer::set_period(uint64_t period_mcs)
    {
        m_period_mcs.store(period_mcs);
    }
}

