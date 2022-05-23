#include "c_graphic_engine.h"

namespace owd_lib
{
	c_graphic_engine* c_graphic_engine::m_singleton = nullptr;
	GLint c_graphic_engine::m_max_batch_textures = 2;

	float c_graphic_engine::fps()
	{
		return m_window.fps();
	}

	bool c_graphic_engine::window_should_close()
	{
		std::mutex mtx{};
		std::lock_guard lock(mtx);
		return glfwWindowShouldClose(m_window.glfw_window());
	}

	void c_graphic_engine::update_window()
	{
		std::mutex mtx{};
		std::lock_guard lock(mtx);
		m_state_upd = m_state_upd_frame;
	}

	void c_graphic_engine::update_entities()
	{
		std::mutex mtx{};
		std::lock_guard lock(mtx);
		m_state_upd = m_state_upd_frame;
	}

	void c_graphic_engine::set_entities_wait()
	{
		m_wait_entities = true;
	}

	void c_graphic_engine::set_entities_ready()
	{
		m_wait_entities = false;
		m_cond_wait_entities.notify_all();
	}

	void c_graphic_engine::set_frame_wait()
	{
		m_wait_frame = true;
	}

	void c_graphic_engine::set_frame_ready()
	{
		m_wait_frame = false;
		m_cond_wait_frame.notify_all();
	}

	void c_graphic_engine::wait_frame()
	{
		std::mutex mtx{};
		std::unique_lock lock(mtx);
		m_wait_frame = true;
		while (true)
		{
			if (!m_wait_frame)
			{
				break;
			}
			m_cond_wait_frame.wait(lock);
		}
	}

	void c_graphic_engine::wait_entities()
	{
		std::mutex mtx{};
		std::unique_lock lock(mtx);
		//m_wait_entities = true;
		while (true)
		{
			if (!m_wait_entities)
			{
				break;
			}
			m_cond_wait_entities.wait(lock);
		}
	}

	std::pair<int32_t, uint32_t> c_graphic_engine::init_opengl()
	{
		auto glfw_init_result = glfwInit();
		ASSERT(glfw_init_result == GLFW_TRUE);
		owd::c_logger logger{ L"opengl initializer" };
		logger << "---- OpenGL initialization START----\n";
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_SAMPLES, 4);
		//glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		auto window_ptr = c_window::get_instance();

		glewExperimental = GL_TRUE;

		auto glew_init_result = glewInit();
		ASSERT(glew_init_result == GLEW_NO_ERROR);

		GL_CALL(glEnable(GL_BLEND));
		GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GL_CALL(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_max_batch_textures));
		logger << "---- OpenGL initialization OK----\n";

		return { glfw_init_result, glew_init_result };
	}

	void c_graphic_engine::run()
	{
		std::mutex mtx{};

		m_logger << "----Window running----\n";
		//m_logger << L"----Òåñò ÚúÚúúÚú----\n";
		//auto ttt = timeBeginPeriod(1);
		//m_frame_start_time = std::chrono::high_resolution_clock::now();
		while (true)
		{
			std::lock_guard lock(mtx);
			if (glfwWindowShouldClose(m_window.glfw_window()))
			{
				m_logger << "----Window closing----\n";
				//glfwTerminate();
				break;
			}
			else
			{
				//default_draw_function();
				//if (m_state_upd == m_state_idle)
				//{
				//}
				//else if(m_state_upd == m_state_upd_entities)
				//{
				//	m_state_upd = m_state_idle;
				//}
				//else if (m_state_upd == m_state_upd_frame)
				//{
				//	//wait_entities();
				//	glfwSwapBuffers(m_window.glfw_window());
				//	glfwPollEvents();
				//	m_state_upd = m_state_idle;
				//}
				//set_frame_ready();
				//m_draw_mutex.lock();
				{
					set_frame_ready();
					wait_entities();
					default_draw_function();

					//m_async_timer.wait();
					//m_frame_end_time = std::chrono::high_resolution_clock::now();
					//int32_t sleep_ms = (m_frame_end_time - m_frame_start_time).count() / 1000 / m_fps;
					//Sleep(sleep_ms);
					/* Swap front and back buffers */
					//set_frame_wait();

					//m_async_timer.wait();
					glfwSwapBuffers(m_window.glfw_window());

					/* Poll for and process events */
					glfwPollEvents();
					//m_async_timer.start(1000000 / 60);
					//m_frame_start_time = std::chrono::high_resolution_clock::now();
					//m_async_timer.start(refresh_period_ms_int());
					
				}
				//m_draw_mutex.unlock();
				owd::sleep_for_ms(1);
			}
			//std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
	
	void c_graphic_engine::set_draw_program(std::function<void()> program)
	{
		m_window.set_program(program);
	}
	
	c_graphic_engine::c_graphic_engine()
		:
		m_opengl_init_result(init_opengl())
	{
		m_logger << "----c_graphic_engine initializing START----\n";
		{
			m_glfw_init_result = m_opengl_init_result.first;
			m_glew_init_result = m_opengl_init_result.second;

			switch (m_glfw_init_result)
			{
			case GLFW_TRUE:  m_logger << "glfwInit OK\n";    break;
			case GLFW_FALSE: m_logger << "glfwInit ERROR\n"; break;

			default:
				m_logger << "glewInit UNKNOWN ERROR\n";
				break;
			}

			switch (m_glew_init_result)
			{
			case GLEW_NO_ERROR:
				m_logger << "glewInit OK\n"; break;
			case GLEW_ERROR_NO_GL_VERSION:
				m_logger << " glewInit ERROR. Description: missing GL version\n";
				break;
			case GLEW_ERROR_GL_VERSION_10_ONLY:
				m_logger << " glewInit ERROR. Description: Need at least OpenGL 1.1\n";
				break;
			case GLEW_ERROR_GLX_VERSION_11_ONLY:
				m_logger << " glewInit ERROR. Description: Need at least GLX 1.2\n";
				break;
			case GLEW_ERROR_NO_GLX_DISPLAY:
				m_logger << " glewInit ERROR. Description: Need GLX display for GLX support\n";
				break;

			default:
				m_logger << "glewInit UNKNOWN ERROR\n";
				break;
			}

			m_draw_function_delegate = std::bind(&c_graphic_engine::default_draw_function, this);

			m_window.set_program(m_draw_function_delegate);

			enable_imgui(false);
		}
		m_logger << "----c_graphic_engine initializing OK----\n";
	}
	void c_graphic_engine::default_draw_function()
	{
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

		//m_rects.draw();
		//m_circles.draw();
		//m_rects_textured.draw();
		m_texture_bank.update_main_thread();
		m_batch_handler.update();
		m_batch_handler.draw();
		//m_test_imgui.update_window();
	}
	
	GLint c_graphic_engine::max_batch_textures()
	{
		return m_max_batch_textures;
	}

	c_graphic_engine* owd_lib::c_graphic_engine::get_instance()
	{
		if (m_singleton == nullptr)
		{
			m_singleton = new c_graphic_engine();
		}

		return m_singleton;
	}
	void c_graphic_engine::terminate()
	{
		if (m_singleton == nullptr)
		{

		}
		else
		{
			m_singleton->m_shader_bank	.terminate();
			m_singleton->m_texture_bank	.terminate();
			//m_singleton->m_test_imgui   .terminate();

			delete m_singleton;
			m_singleton = nullptr;
			c_window::terminate();
		}
	}
    c_graphic_engine::~c_graphic_engine()
    {
    }
	//void c_graphic_engine::add_rect(float centre_x, float centre_y, float width, float height,
	//	float red, float green, float blue, float alpha, uint16_t level)
	//{
	//	m_batch_handler.add_rect(centre_x, centre_y, width, height, red, green, blue, alpha, level);
	//}
	//void c_graphic_engine::add_circle(float centre_x, float centre_y, float radius, 
	//	float red, float green, float blue, float alpha, uint16_t level)
	//{
	//	m_batch_handler.add_circle(centre_x, centre_y, radius, red, green, blue, alpha, level);
	//}
	//void c_graphic_engine::add_textured(float centre_x, float centre_y, float width, float height, 
	//	texture_t& texture, uint16_t level)
	//{
	//	m_batch_handler.add_textured(centre_x, centre_y, width, height, texture, level);
	//}
}
