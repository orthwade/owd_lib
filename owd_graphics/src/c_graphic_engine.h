#pragma once
#include "c_window.h"
#include "c_texture_bank.h"
#include "c_shader_bank.h"
#include "batches/c_batch_handler.h"

namespace owd_lib
{
	class c_graphic_engine
	{
	public:
		/// <summary>
		/// Start updating window. 
		/// </summary>
		void run();

		/// <summary>
		/// Set function executed per frame.
		/// </summary>
		/// <param name="draw"></param>
		void set_draw_program(std::function<void()> draw);

		/// <summary>
		/// Get normalized horizontal coordinate:
		/// norm_x ==  1.0f is right border of the window;
		/// norm_x == -1.0f is left border of the window;
		/// </summary>
		/// <param name="x">Absolute coordinate. If the window is square, x == norm_x.</param>
		/// <returns></returns>
		inline float norm_x(float x)
		{
			return (m_window.aspect_ratio()) * x;
		}

		/// <summary>
		/// Get normalized vertical coordinate:
		/// norm_y ==  1.0f is top of the window;
		/// norm_y == -1.0f is bottom of the window;
		/// </summary>
		/// <param name="y">Absolute coordinate. If the window is square, y == norm_y.</param>
		/// <returns></returns>
		inline float norm_y(float y)
		{
			return y;
		}

		/// <summary>
		/// Enable debug window.
		/// </summary>
		/// <param name="enabled"></param>
		inline void enable_imgui(bool enabled = true)
		{
			//m_test_imgui.enabled = enabled;
		}

		/// <summary>
		/// Load shader to shader bank.
		/// Name of the shader will be a copy of filepath.
		/// </summary>
		/// <param name="filepath"></param>
		/// <returns></returns>
		inline bool load_shader(std::wstring_view filepath)
		{
			return m_shader_bank.load(filepath);
		}

		/// <summary>
		/// Load shader to shader bank and specify its name.
		/// </summary>
		/// <param name="filepath"></param>
		/// <param name="name"></param>
		/// <returns></returns>
		inline bool load_shader(std::wstring_view filepath, std::wstring_view name)
		{
			return m_shader_bank.load(filepath, name);
		}
		
		/// <summary>
		/// Get shader from shader bank by index.
		/// If index is out of range, returnes empty shader.
		/// </summary>
		/// <param name="i"></param>
		/// <returns></returns>
		inline std::shared_ptr<c_shader>& shader_by_index(uint64_t i)
		{
			return m_shader_bank.by_index(i);
		}

		/// <summary>
		/// Get shader from shader bank by name.
		/// If name is absent in the bank, returnes empty shader.
		/// </summary>
		/// <param name="i"></param>
		/// <returns></returns>
		inline std::shared_ptr<c_shader>& shader_by_name(std::wstring_view name)
		{
			return m_shader_bank.by_name(name);
		}

		/// <summary>
		/// Get shader from shader bank by filepath.
		/// If filepath is absent in the bank, returnes empty shader.
		/// </summary>
		/// <param filepath="i"></param>
		/// <returns></returns>
		inline std::shared_ptr<c_shader>& shader_by_filepath(std::wstring_view filepath)
		{
			return m_shader_bank.by_filepath(filepath);
		}

		/// <summary>
		/// Load texture to texture bank.
		/// Name of the texture will be a copy of filepath.
		/// </summary>
		/// <param name="filepath"></param>
		/// <returns></returns>
		/*inline bool load_texture(std::wstring_view filepath)
		{
			return m_texture_bank.load(filepath);
		}*/

		inline texture_t& load_and_get_texture(std::wstring_view filepath)
		{
			return m_texture_bank.load_and_get(filepath);
		}

		/// <summary>
		/// Load texture to texture bank and specify its name.
		/// </summary>
		/// <param name="filepath"></param>
		/// <param name="name"></param>
		/// <returns></returns>
		inline bool load_texture(std::wstring_view filepath, std::wstring_view name)
		{
			return m_texture_bank.load(filepath, name);
		}

		/// <summary>
		/// Get texture from texture bank by index.
		/// If index is out of range, returnes empty texture.
		/// </summary>
		/// <param name="i"></param>
		/// <returns></returns>
		inline std::shared_ptr<c_texture>& texture_by_index(uint64_t i)
		{
			return m_texture_bank.by_index(i);
		}

		/// <summary>
		/// Get texture from texture bank by name.
		/// If name is absent in the bank, returnes empty texture.
		/// </summary>
		/// <param name="i"></param>
		/// <returns></returns>
		inline std::shared_ptr<c_texture>& texture_by_name(std::wstring_view name)
		{
			return m_texture_bank.by_name(name);
		}

		/// <summary>
		/// Get texture from texture bank by filepath.
		/// If filepath is absent in the bank, returnes empty texture.
		/// </summary>
		/// <param filepath="i"></param>
		/// <returns></returns>
		inline std::shared_ptr<c_texture>& texture_by_filepath(std::wstring_view filepath)
		{
			return m_texture_bank.by_filepath(filepath);
		}
		
		/// <summary>
		/// Get maximum count of textured binded at once supported by fragment shader.
		/// </summary>
		/// <returns></returns>
		static GLint max_batch_textures();

		/// <summary>
		/// Get pointer to graphic engine singleton.
		/// </summary>
		/// <returns></returns>
		static c_graphic_engine* get_instance();

		/// <summary>
		/// Delete graphic engine singleton.
		/// Singleton isn't deleted in default destructor.
		/// </summary>
		/// <returns></returns>
		static void terminate();

		/// <summary>
		/// Get batches of coloured rectangles
		/// </summary>
		/// <returns></returns>
		//inline c_batches_coloured_rect& get_batches_coloured_rect() { return m_rects; }

		/// <summary>
		/// Get batches of coloured circles.
		/// </summary>
		/// <returns></returns>
		//inline c_batches_coloured_circle& get_batches_coloured_circle() { return m_circles; }

		/// <summary>
		/// Get batches of textured rectangles.
		/// </summary>
		/// <returns></returns>
		//inline c_batches_textured& get_batches_textured_rects() { return m_rects_textured; }

		inline c_batch_handler& get_batch_handler() { return m_batch_handler; }

	protected:
		owd::c_logger m_logger{ L"graphic_engine_logger" };
		static std::pair<int32_t, uint32_t> init_opengl();
		std::pair<int32_t, uint32_t> m_opengl_init_result{};
		static GLint m_max_batch_textures;

		c_shader_bank* m_shader_bank_ptr = c_shader_bank::get_instance();
		c_shader_bank& m_shader_bank = *m_shader_bank_ptr;

		c_window* m_window_ptr = c_window::get_instance();
		c_window& m_window = *m_window_ptr;

		c_texture_bank* m_texture_bank_ptr = c_texture_bank::get_instance();
		c_texture_bank& m_texture_bank = *m_texture_bank_ptr;

		int32_t  m_glfw_init_result{};
		uint32_t m_glew_init_result{};

		std::function<void()> m_draw_function_delegate{};
		
		float m_rect_x = -1.0f;
		float m_rect_y = -1.0f;

		float m_rect_1_x = 1.0f;
		float m_rect_1_y = -1.0f;

		float increment_x = 0.01f;
		float increment_y = 0.01f;

		float increment_1_x = 0.01f;
		float increment_1_y = 0.01f;

		float increment_red = 0.01f;
		float m_red = 0.0f;

		float increment_green = 0.01f;
		float m_green = 0.0f;
		
		//c_batches_textured m_rects_textured{};
		//c_batches_coloured_circle m_circles{};
		//c_batches_coloured_rect m_rects{};

		c_batch_handler* m_batch_handler_ptr = c_batch_handler::get_instance();

		c_batch_handler& m_batch_handler = *m_batch_handler_ptr;

		void default_draw_function();
		static c_graphic_engine* m_singleton;

		c_graphic_engine();
		~c_graphic_engine();
		
		c_graphic_engine(const c_graphic_engine&) = delete;
		c_graphic_engine& operator=(const c_graphic_engine&) = delete;

		/*void add_rect(float centre_x, float centre_y, float width, float height,
			float red, float green, float blue, float alpha, uint16_t level);

		void add_circle(float centre_x, float centre_y, float radius,
			float red, float green, float blue, float alpha, uint16_t level);

		void add_textured(float centre_x, float centre_y, float width, float height,
			texture_t& texture, uint16_t level);*/

	};
}