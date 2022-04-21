#pragma once
#include <algorithm>

#include <owd_math.h>

#include "../c_vertex_buffer.h"
#include "../c_index_buffer.h"
#include "../c_vertex_array.h"
#include "../c_vertex_buffer_layout.h"
#include "../c_shader.h"
#include "../c_mat4_uniform.h"
#include "../c_window.h"
#include "../c_shader_bank.h"


namespace owd_lib
{
	struct s_colour
	{
		float red{};
		float green{};
		float blue{};
		float alpha{};
	};

	class c_graphic_unit_lib
	{
	public:
		enum class enm_state
		{
			not_init,
			good,
			deleted
		};
		c_graphic_unit_lib();
		c_graphic_unit_lib(const vertices_t& vertex_positions, const gl_indices_t& indices);
		c_graphic_unit_lib(const vertices_t& vertex_positions, const gl_indices_t& indices,
			float red, float green, float blue, float alpha);
		c_graphic_unit_lib(const vertices_t& vertex_positions, const gl_indices_t& indices,
			float red, float green, float blue, float alpha, uint16_t level);

		~c_graphic_unit_lib() = default;

		void set(const vertices_t& vertex_positions, const gl_indices_t& indices);

		void set(const vertices_t& vertex_positions, const gl_indices_t& indices,
			float red, float green, float blue, float alpha);

		void set(float centre_x, float centre_y,
			float red, float green, float blue, float alpha);

		void set_position(float centre_x, float centre_y);
		void move(float delta_x, float delta_y);

		void resize(float size_multiplier);

		void set_colour(float red, float green, float blue, float alpha);

		inline vertices_t& vertices() { return m_vertices; }
		inline vertices_t& vertex_positions() { return m_vertex_positions; }

		inline gl_indices_t& indices_no_batch() { return m_indices; }

		gl_indices_t indices_batch(gl_index_t max_index);

		inline gl_index_t max_index() { return *std::max_element(m_indices.begin(), m_indices.end()); }

		bool m_should_update = false;

		gl_index_t m_index_in_batch = 0;
		inline void set_to_delete() { m_state = enm_state::deleted; }

		inline enm_state state() const { return m_state; }

		inline bool deleted() const { return m_state == enm_state::deleted; }

		inline s_colour& colour() { return m_colour; }

		inline uint16_t level() { return m_level; }

		static std::shared_ptr<c_graphic_unit_lib>& empty_unit();
		static owd::xy_t centre(const vertices_t& vertex_positions, const gl_indices_t& indices);
		
		inline owd::xy_t& centre() { return m_centre; }

	private:
		static GLint  m_max_vertices;
		static GLint  m_max_indices;
		static size_t m_max_units_in_one_batch;

		static std::shared_ptr<c_graphic_unit_lib> m_empty_unit;

		uint16_t m_level = 0;

		vertices_t   m_vertex_positions{};
		vertices_t   m_vertices{};
		gl_indices_t m_indices {};
		owd::xy_t m_centre{};
		s_colour m_colour{};

		enm_state m_state = enm_state::not_init;
	};
}