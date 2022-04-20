#pragma once
#include <functional>
#include <mutex>

#include <owd_misc.h>
#include <owd_time.h>

#include "opengl/opengl.h"

namespace owd_lib
{
	class c_window : public owd::c_basic_object
	{
	public:
		void set_fps(uint64_t fps);

		uint64_t fps(uint64_t fps);

		float refresh_period_mcs();
		uint64_t refresh_period_mcs_int();
		float refresh_period_s();
		uint64_t refresh_period_ms_int();

		inline int64_t refresh_period_ns();

		void resize(uint16_t w, uint16_t h);

		void run();

		void set_program(std::function<void()> program);

		void set_shader_program(uint32_t);

		float aspect_ratio();

		inline GLFWwindow* glfw_window()
		{
			return m_glfw_window;
		}

		static c_window* get_instance();
		static void terminate();

	protected:
		GLFWwindow* m_glfw_window = nullptr;

		int m_w = 960;
		int m_h = 540;

		int m_frame_buffer_w = 960;
		int m_frame_buffer_h = 540;

		uint32_t m_shader_program_id{};
		//c_cycle_thread m_window_thread{};

		//std::atomic_bool m_window_exists = false;
		float m_fps = 60.0f;

		std::function<void()> m_draw;

		std::chrono::steady_clock::time_point m_frame_start_time{};
		std::chrono::steady_clock::time_point m_frame_end_time{};

		int64_t m_frame_time_ns{};

		void m_frame_buffer_resize_callback(GLFWwindow* window,
			int frame_buffe_width,
			int frame_buffe_height);

		//c_graphic_renderer* m_renderer_ptr = nullptr;
		std::recursive_mutex m_draw_mutex{};
		
		owd::c_async_timer m_async_timer{};

		static c_window* m_singleton;

		c_window();
		~c_window();
		
		c_window(const c_window&) = delete;
		c_window& operator=(const c_window&) = delete;
	};
}