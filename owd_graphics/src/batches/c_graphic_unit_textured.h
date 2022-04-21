#pragma once
#include "c_graphic_unit.h"
#include "../c_texture_uniform.h"
#include "../c_texture_bank.h"

namespace owd_lib
{
	class c_graphic_unit_textured
	{
	public:
		enum class enm_state
		{
			not_init,
			empty,
			good,
			deleted
		};

		c_graphic_unit_textured();
		//c_graphic_unit_textured(const vertices_t& vertex_positions, const gl_indices_t& indices);
		c_graphic_unit_textured(float centre_x, float centre_y, float width, float height,
			texture_t& texture, uint16_t level);

		/*c_graphic_unit_textured(const vertices_t& vertex_positions, const gl_indices_t& indices,
			float red, float green, float blue, float alpha);
		c_graphic_unit_textured(const vertices_t& vertex_positions, const gl_indices_t& indices,
			float red, float green, float blue, float alpha, uint16_t level);*/

		~c_graphic_unit_textured() = default;
		inline texture_t& get_texture() { return m_texture; }
		//void set(const vertices_t & vertex_positions, const gl_indices_t & indices);

		//void set(const vertices_t & vertex_positions, const gl_indices_t & indices,
		//	float red, float green, float blue, float alpha);

		//void set(float centre_x, float centre_y,
		//	float red, float green, float blue, float alpha);

		void set_position(float centre_x, float centre_y);
		void move(float delta_x, float delta_y);

		void resize(float size_multiplier);

		//void set_colour(float red, float green, float blue, float alpha);

		vertices_t vertices();
		
		vertices_t vertex_positions();

		inline gl_indices_t& indices_no_batch() { return m_indices; }

		gl_indices_t indices_batch(gl_index_t max_index);

		//inline gl_index_t max_index() { return *std::max_element(m_indices.begin(), m_indices.end()); }

		bool m_should_update = false;

		gl_index_t m_index_in_batch = 0;
		inline void set_to_delete() { m_state = enm_state::deleted; }

		inline enm_state state() const { return m_state; }

		inline bool deleted() const { return m_state == enm_state::deleted; }

		inline s_colour& colour() { return m_colour; }

		inline uint16_t level() { return m_level; }


		static std::shared_ptr<c_graphic_unit_textured>& empty_unit();
		static owd::xy_t centre(const vertices_t& vertex_positions, const gl_indices_t& indices);
		inline owd::xy_t& centre() { return m_centre; }

		float m_index = 0.0f;

	private:
		static GLint  m_max_vertices;
		static GLint  m_max_indices;
		static size_t m_max_units_in_one_batch;

		static std::shared_ptr<c_graphic_unit_textured> m_empty_unit;

		uint16_t m_level = 0;

		float m_x{ -0.5f };
		float m_y{ 0.0f };

		float m_w{ 0.5f };
		float m_h{ 0.5f };

		texture_t m_texture{};

		vertices_t   m_vertices{};
		static gl_indices_t m_indices;
		owd::xy_t m_centre{};
		s_colour m_colour{};

		enm_state m_state{ enm_state::not_init };
	};

	typedef std::shared_ptr<c_graphic_unit_textured> g_unit_textured_t;

}