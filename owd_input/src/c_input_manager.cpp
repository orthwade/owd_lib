#include "c_input_manager.h"

namespace owd_lib
{
	c_input_manager* c_input_manager::m_singleton = nullptr;

	c_input_manager* owd_lib::c_input_manager::get_instance()
	{
		if (m_singleton == nullptr)
		{
			m_singleton = new c_input_manager();
		}

		return m_singleton;
	}
	void c_input_manager::terminate()
	{
		if (m_singleton == nullptr)
		{

		}
		else
		{
			delete m_singleton;
			m_singleton = nullptr;
		}
	}
	s_key& c_input_manager::get_key(int32_t key_code)
	{
		auto lock = std::lock_guard(m_mutex);
		for (uint64_t i = 0; i != m_keys.size(); ++i)
		{
			if (m_keys[i].key == key_code)
			{
				return m_keys[i];
			}
		}

		m_keys.push_back({ key_code, key_release });
		return m_keys.back();
	}
	
	c_input_manager::c_input_manager()
	{
		auto ptr = c_graphic_engine::get_instance();
		glfwSetKeyCallback(c_window::get_instance()->glfw_window(), key_callback);
		glfwSetMouseButtonCallback(c_window::get_instance()->glfw_window(), mouse_button_callback);
		//glfwSetCursorPosCallback(c_window::get_instance()->glfw_window(), cursor_position_callback);
	}
	c_input_manager::~c_input_manager()
	{
	}
	void key_callback(GLFWwindow* window, int32_t key_code, int32_t scancode, int32_t action, int32_t mods)
	{
		auto input_manager = c_input_manager::get_instance();
		auto& key_ = input_manager->get_key(key_code);
		std::mutex mtx{};
		auto lock = std::lock_guard(mtx);

		key_.key = key_code;
		if (action == GLFW_PRESS)
		{
			key_.state = key_press;
		}
		else
		{
			key_.state = key_release;
		}
	}
	void mouse_button_callback(GLFWwindow* window, int32_t button, int32_t action, int32_t mods)
	{
		auto input_manager = c_input_manager::get_instance();
		auto& key_ = input_manager->get_key(button);
		std::mutex mtx{};
		auto lock = std::lock_guard(mtx);
		key_.key = button;
		if (action == GLFW_PRESS)
		{
			key_.state = key_press;
		}
		else
		{
			key_.state = key_release;
		}
	}

	static double m_x{};
	static double m_y{};
	double c_input_manager::mouse_x()
	{
		std::mutex mtx{};
		std::lock_guard lock(mtx);
		auto wnd = c_window::get_instance();
		glfwGetCursorPos(wnd->glfw_window(), &m_x, &m_y);
		

		double w = wnd->width();
		double h = wnd->height();
		//m_x /= h;
		//m_y /= h;

		//m_y = 1.0 - m_y;
		//m_y = m_y * 2.0 - 1.0;

		//m_x = m_x * 2.0 - 1.0;

		m_x = m_x - 0.5 * w;
		m_x /= (h / 2.0);
		return m_x;
	}
	double c_input_manager::mouse_y()
	{
		std::mutex mtx{};
		std::lock_guard lock(mtx);
		auto wnd = c_window::get_instance();
		glfwGetCursorPos(c_window::get_instance()->glfw_window(), &m_x, &m_y);
		
		double h = wnd->height();
		//m_x /= h;
		m_y /= h;

		m_y = 1.0 - m_y;
		m_y = m_y * 2.0 - 1.0;

		//m_x = m_x * 2.0 - 1.0;
		return m_y;
	}
	/*void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		std::mutex mtx{};
		std::lock_guard lock(mtx);
		m_x = xpos;
		m_y = ypos;
	}*/
}