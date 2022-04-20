#pragma once
#include "c_graphic_unit.h"

namespace owd_lib
{
	typedef std::shared_ptr<c_graphic_unit_lib> g_unit_t;
	class c_graphic_batch
	{
	public:
		c_graphic_batch();
		c_graphic_batch(uint16_t level);

		~c_graphic_batch() = default;

		void add(g_unit_t& unit);
		void draw();

		inline size_t indices_count() { return m_index_buffer.count(); }
		inline size_t vertices_count() { return m_vertex_buffer.count(); }
		inline static g_unit_t& empty_unit() { return c_graphic_unit_lib::empty_unit(); }
		g_unit_t& get_unit(owd::index_t index);
		g_unit_t& get_last_unit();

		inline std::vector<g_unit_t>& get_vec() { return m_vec; }

		void erase(owd::index_t index);
		
		inline gl_index_t max_index() { return m_index_buffer.max_index(); }

	private:
		uint16_t m_level = 0;

		c_vertex_buffer			m_vertex_buffer{};
		c_index_buffer			m_index_buffer{};
		c_vertex_array			m_vertex_array{};

		c_vertex_buffer_layout	m_vertex_buffer_layout{};

		vertices_t  m_vertices_buffer{};
		gl_indices_t m_indices_buffer{};

		bool m_should_update = false;

		std::vector<g_unit_t> m_vec{};

		void update();
	};
}