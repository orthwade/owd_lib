#pragma once
#include <unordered_map>

#include "c_graphic_batch.h"
#include "c_graphic_batch_textured.h"
#include "../c_texture_uniform.h"

namespace owd_lib
{
	typedef std::shared_ptr<c_graphic_batch> g_batch_t;
	typedef std::shared_ptr<c_graphic_batch_textured> g_batch_textured_t;
	struct s_level
	{
		std::vector<g_batch_t>          batches{};
		std::vector<g_batch_textured_t> batches_textured{};
	};
	class c_batch_handler
	{
		struct s_buffer_fig
		{
			std::vector<float> positions;
			std::vector<uint32_t> indices;
			float r; float g; float b; float a; uint16_t l; owd::index_t key;
		};
		struct s_buffer_rec
		{
			float x; float y; float w; float h;
			float r; float g; float b; float a; uint16_t l; owd::index_t key;
		};
		struct s_buffer_cir
		{
			float x; float y; float radius;
			float r; float g; float b; float a; uint16_t l; owd::index_t key;
		};
		struct s_buffer_tex
		{
			float x; float y; float w; float h;
			std::wstring t; uint16_t l; owd::index_t key;
		};
		struct s_buffer
		{
			std::list<s_buffer_fig> list_buffer_fig;
			std::list<s_buffer_rec> list_buffer_rec;
			std::list<s_buffer_cir> list_buffer_cir;
			std::list<s_buffer_tex> list_buffer_tex;
		};

	public:
		void* add(const std::vector<float>& positions, const std::vector<uint32_t>& indices,
			float r, float g, float b, float a, uint16_t l);

		void* add(float x, float y, float w, float h,
			float r, float g, float b, float a, uint16_t l);

		void* add(float x, float y, float radius,
			float r, float g, float b, float a, uint16_t l);

		void* add(float x, float y, float w, float h,
			std::wstring_view t, uint16_t l);

		void clear();
		void draw();

		void update();

		static c_batch_handler* get_instance();
		static void terminate();

	private:
		owd::index_t m_key = 0;
		std::unordered_map<owd::index_t, void*> m_unit_map{};
		std::recursive_mutex m_mtx{};
		std::list<g_unit_t> m_list_unit{};
		std::list<g_unit_textured_t> m_list_unit_textured{};
		GLint m_max_vertices{};
		GLint m_max_indices{};

		std::vector<s_level> m_levels{};
	
		c_window* m_window = c_window::get_instance();

		shader_t m_shader_coloured{};
		shader_t m_shader_textured{};

		c_texture_uniform m_texture_uniform{};

		c_mat4_uniform m_mat4_uniform_coloured{};
		c_mat4_uniform m_mat4_uniform_textured{};

		owd::c_mat4 m_projection{};

		GLint m_max_texture_image_units = 2;

		//std::pair<uint32_t, int32_t> get_common_and_local_indices(owd::index_t index);

		s_level& get_level(uint16_t level);

		


		bool vertices_exceed(g_batch_t& batch, g_unit_t& unit);
		bool indices_exceed(g_batch_t& batch, g_unit_t& unit);
		bool units_count_exceeds(g_batch_t& batch, g_unit_t& unit);

		void* add_main_thread(g_unit_t& unit);
		void* add_main_thread(g_unit_textured_t& unit);

		void* add_rect_main_thread(float centre_x, float centre_y, float width, float height,
			float red, float green, float blue, float alpha, uint16_t level);

		void* add_circle_main_thread(float centre_x, float centre_y, float radius,
			float red, float green, float blue, float alpha, uint16_t level);

		void* add_textured_main_thread(float centre_x, float centre_y, float width, float height,
			texture_t& texture, uint16_t level);

		static c_batch_handler* m_singleton;

		c_batch_handler();
		~c_batch_handler();

		c_batch_handler(const c_batch_handler&) = delete;
		c_batch_handler& operator=(const c_batch_handler&) = delete;

	};
}