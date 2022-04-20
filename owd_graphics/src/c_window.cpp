#include "c_window.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

namespace owd_lib
{
	c_window* c_window::m_singleton = nullptr;
	
	static void global_frame_buffer_resize_callback
	(GLFWwindow* window, int frame_buffer_width, int frame_buffer_height)
	{
		glViewport(0, 0, frame_buffer_width, frame_buffer_height);
	}
	/*void c_window::set_size(uint16_t h, uint16_t w)
	{

	}*/
	void c_window::set_fps(uint64_t fps)
	{
		//m_mtx.lock();
		{
			m_fps = fps;
		}
		//m_mtx.unlock();
	}
	uint64_t c_window::fps(uint64_t fps)
	{
		uint64_t result{};
		//m_mtx.lock();
		{
			result = m_fps;
		}
		//m_mtx.unlock();
		return result;
	}
	float c_window::refresh_period_mcs()
	{
		//float result{};
		////m_mtx.lock();
		//{
		//	result = 1000000.0f / m_fps;
		//}
		//m_mtx.unlock();
		return 1000000.0f * refresh_period_s();
	}
	uint64_t c_window::refresh_period_mcs_int()
	{
		return static_cast<uint64_t>(1000000.0f / m_fps);
	}
	float c_window::refresh_period_s()
	{
		return 1.0f / m_fps;
	}
	inline int64_t c_window::refresh_period_ns()
	{
		return static_cast<int64_t>(1000000000.0f / m_fps);
	}

	void c_window::resize(uint16_t w, uint16_t h)
	{
		//m_mtx.lock();
		{
			m_logger << "Resizing window: width: " << w << ";    height: " << h << '\n';

			m_w = w;
			m_h = h;

			//glViewport(0, 0, m_w, m_h);
		}
		//m_mtx.unlock();
	}
	uint64_t c_window::refresh_period_ms_int()
	{
		return static_cast<uint64_t>(ceil(1000.0f / this->m_fps));
	}
	void c_window::run()
	{
		m_logger << "----Window running----\n";
		//m_logger << L"----Òåñò ÚúÚúúÚú----\n";
		
		while (true)
		{
			if (glfwWindowShouldClose(m_glfw_window))
			{
				m_logger << "----Window closing----\n";
				//glfwTerminate();
				break;
			}
			else
			{
				//m_draw_mutex.lock();
				{
					
					m_draw();
					
					m_async_timer.wait();
					/* Swap front and back buffers */
					glfwSwapBuffers(m_glfw_window);

					/* Poll for and process events */
					glfwPollEvents();
					m_async_timer.start(refresh_period_mcs_int());
				}
				//m_draw_mutex.unlock();
			}
		}
	}
	void c_window::set_program(std::function<void()> program)
	{
		//m_mtx.lock();
		{
			m_logger << "Setting draw program(function)\n";
			{
				m_draw = program;
			}
			m_logger << "Setting draw program(function)\n";
		}
		//m_mtx.unlock();
	}
	void c_window::set_shader_program(uint32_t input)
	{
		m_shader_program_id = input;
	}
	float c_window::aspect_ratio()
	{
		return static_cast<float>(m_w) / static_cast<float>(m_h);
	}
	void c_window::m_frame_buffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
	{
		//m_mtx.lock();
		{

		}
		//m_mtx.unlock();
	}

	c_window* owd_lib::c_window::get_instance()
	{
		if (m_singleton == nullptr)
		{
			m_singleton = new c_window();
		}

		return m_singleton;
	}
	void c_window::terminate()
	{
		if (m_singleton == nullptr)
		{

		}
		else
		{
			glfwTerminate(); 
			delete m_singleton;
			m_singleton = nullptr;
		}
	}
    c_window::c_window()
    {
		set_name(L"window");
		m_logger.set_name(L"window_logger");
		//m_mtx.lock();
		{
			m_logger << "Initializing window\n";

			m_glfw_window = glfwCreateWindow(m_w, m_h, "default glfw window", NULL, NULL);

			if (m_glfw_window == NULL)
			{
				m_logger << "glfwCreateWindow ERROR\n";
			}

			glfwMakeContextCurrent(m_glfw_window);

			glfwSwapInterval(0);

			//auto mm = glfwGetVideoMode(glfwGetPrimaryMonitor());
			//int32_t i{};
		}


		m_logger << "Initializing window OK\n";
    }
    c_window::~c_window()
    {
    }

}
