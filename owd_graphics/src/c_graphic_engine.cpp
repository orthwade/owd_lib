#include "c_graphic_engine.h"

namespace owd_lib
{
	c_graphic_engine* c_graphic_engine::m_singleton = nullptr;
	GLint c_graphic_engine::m_max_batch_textures = 2;

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
		m_logger << "----Running graphic engine START----\n";
		{
			m_window.run();
		}
		m_logger << "----Running graphic engine END----\n";
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
