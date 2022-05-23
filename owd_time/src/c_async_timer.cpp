#include "c_async_timer.h"
static auto set_time_resolution = timeBeginPeriod(1);
namespace owd_lib
{
    c_async_timer_lib::c_async_timer_lib()
    {
    }
    c_async_timer_lib::c_async_timer_lib(uint64_t period_ms)
    {
        //init(period_ms);
        set_period(period_ms);
    }
    c_async_timer_lib::~c_async_timer_lib()
    {
        terminate();
    }
    void c_async_timer_lib::init()
    {
        terminate();
        m_thread_exists = true;
        m_thread = std::thread(&c_async_timer_lib::do_, this);
    }
    void c_async_timer_lib::init(uint64_t period_mcs)
    {
        terminate();
        m_thread_exists = true;
        set_period(period_mcs);
        m_thread = std::thread(&c_async_timer_lib::do_, this);
    }
    void c_async_timer_lib::terminate()
    {
        stop();
        m_thread_exists = false;
        if (m_thread.joinable())
        {
            m_thread.join();
        }
    }
    void c_async_timer_lib::start(uint64_t period_mcs)
    {
        set_period(period_mcs);
        m_state = enm_state::waiting;
    }
    void c_async_timer_lib::start()
    {
        m_state = enm_state::waiting;
    }
    void c_async_timer_lib::do_()
    {
        while (m_thread_exists)
        {
            if (m_state == enm_state::waiting)
            {
                m_frame_start_time = std::chrono::high_resolution_clock::now();
               
                sleep_(m_period_mcs / 1000 - 2);
                while (true)
                {
                    //sleep_();
                    /*m_frame_duration_int_ms =
                        std::chrono::duration_cast<std::chrono::microseconds>
                        (std::chrono::high_resolution_clock::now() - m_frame_start_time).count();*/

                    if (std::chrono::high_resolution_clock::now() >=
                        m_frame_start_time + std::chrono::microseconds(static_cast<int32_t>(m_period_mcs)))
                    {
                        m_state = enm_state::done;
                        break;
                    }
                }
                m_state = enm_state::done;
                m_conditional.notify_all();
            }
        }
    }
    void c_async_timer_lib::sleep_(uint64_t ms)
    {
        sleep_ms(ms);
    }
    void c_async_timer_lib::wait()
    {
        std::unique_lock lock(m_mtx);
        //m_conditional.wait(lock, (m_state == enm_state::done));
        while (m_state == enm_state::waiting)
        {
            //sleep_(1);
            m_conditional.wait(lock);
        }
    }
    //void c_async_timer_lib::wait()
    //{
    //    std::condition_variable cv{};
    //    std::mutex mtx{};
    //    std::unique_lock lock(mtx);
    //    cv.wait(lock, (m_state == enm_state::done));
    //}
    void c_async_timer_lib::stop()
    {
        m_state = enm_state::done;
    }
    void c_async_timer_lib::set_period(uint64_t period_ms)
    {
        m_period_mcs.store(period_ms);
    }
}

