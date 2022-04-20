#include "c_graphic_unit.h"

namespace owd_lib
{
	std::shared_ptr<c_graphic_unit_lib> c_graphic_unit_lib::m_empty_unit = std::shared_ptr<c_graphic_unit_lib>();

	GLint c_graphic_unit_lib::m_max_vertices = 0;
	GLint c_graphic_unit_lib::m_max_indices  = 0;

	size_t c_graphic_unit_lib::m_max_units_in_one_batch = 0;

	c_graphic_unit_lib::c_graphic_unit_lib()
	{
		m_should_update = true;
	}

	c_graphic_unit_lib::c_graphic_unit_lib(const vertices_t& vertex_positions, const gl_indices_t& indices)
		: c_graphic_unit_lib(vertex_positions, indices, 0.0f, 0.0f, 0.0f, 0.0f, 0)
	{
	}

	c_graphic_unit_lib::c_graphic_unit_lib(const vertices_t& vertex_positions, const gl_indices_t& indices,
		float red, float green, float blue, float alpha)
		: c_graphic_unit_lib(vertex_positions, indices, red, green, blue, alpha, 0)
	{
	}
	c_graphic_unit_lib::c_graphic_unit_lib(const vertices_t& vertex_positions, const gl_indices_t& indices, 
		float red, float green, float blue, float alpha, 
		uint16_t level) :
		m_vertex_positions(vertex_positions),
		m_indices(indices),
		m_colour({ red, green, blue, alpha }),
		m_level(level)
	{
		m_centre = centre(vertex_positions, indices);
		m_vertices.resize(3 * m_vertex_positions.size());

		owd::index_t vertex_positions_index = 0;
		owd::index_t vertices_index = 0;

		while (vertex_positions_index < m_vertex_positions.size())
		{
			m_vertices[vertices_index] = m_vertex_positions[vertex_positions_index];
			m_vertices[vertices_index + 1] = m_vertex_positions[vertex_positions_index + 1];
			m_vertices[vertices_index + 2] = red;
			m_vertices[vertices_index + 3] = green;
			m_vertices[vertices_index + 4] = blue;
			m_vertices[vertices_index + 5] = alpha;

			vertex_positions_index += 2;
			vertices_index += 6;
		}
		m_should_update = true;
	}

	void c_graphic_unit_lib::set(const vertices_t& vertex_positions, const gl_indices_t& indices)
	{
		wait_init();
		m_vertex_positions = vertex_positions;
		m_indices  = indices;
		m_centre = centre(vertex_positions, indices);
		m_vertices.resize(3 * m_vertex_positions.size());

		owd::index_t vertex_positions_index = 0;
		owd::index_t vertices_index = 0;

		while (vertex_positions_index < m_vertex_positions.size())
		{
			m_vertices[vertices_index] = m_vertex_positions[vertex_positions_index];
			m_vertices[vertices_index + 1] = m_vertex_positions[vertex_positions_index + 1];

			vertex_positions_index += 2;
			vertices_index         += 6;
		}
		m_should_update = true;
	}

	void c_graphic_unit_lib::set(const vertices_t& vertex_positions, const gl_indices_t& indices, 
		float red, float green, float blue, float alpha)
	{
		wait_init();
		m_vertex_positions = vertex_positions;
		m_indices = indices;
		m_colour = { red, green, blue, alpha };
		m_centre = centre(vertex_positions, indices);
		m_vertices.resize(3 * m_vertex_positions.size());

		owd::index_t vertex_positions_index = 0;
		owd::index_t vertices_index         = 0;

		while (vertex_positions_index < m_vertex_positions.size())
		{
			m_vertices[vertices_index]     = m_vertex_positions[vertex_positions_index];
			m_vertices[vertices_index + 1] = m_vertex_positions[vertex_positions_index + 1];
			m_vertices[vertices_index + 2] = red;
			m_vertices[vertices_index + 3] = green;
			m_vertices[vertices_index + 4] = blue;
			m_vertices[vertices_index + 5] = alpha;

			vertex_positions_index += 2;
			vertices_index         += 6;
		}
		m_should_update = true;
	}

	void c_graphic_unit_lib::set(float centre_x, float centre_y, float red, float green, float blue, float alpha)
	{
		wait_init();
		m_colour = { red, green, blue, alpha };

		owd::index_t vertex_positions_index = 0;
		owd::index_t vertices_index = 0;

		float delta_x = centre_x - m_centre.x;
		float delta_y = centre_y - m_centre.y;

		while (vertex_positions_index < m_vertex_positions.size())
		{
			m_vertex_positions[vertex_positions_index]     += delta_x;
			m_vertex_positions[vertex_positions_index + 1] += delta_y;

			m_vertices[vertices_index]     = m_vertex_positions[vertex_positions_index];
			m_vertices[vertices_index + 1] = m_vertex_positions[vertex_positions_index + 1];
			m_vertices[vertices_index + 2] = red;
			m_vertices[vertices_index + 3] = green;
			m_vertices[vertices_index + 4] = blue;
			m_vertices[vertices_index + 5] = alpha;

			vertex_positions_index += 2;
			vertices_index += 6;
		}
		m_centre = { centre_x, centre_y };
		m_should_update = true;
	}

	void c_graphic_unit_lib::set_position(float centre_x, float centre_y)
	{
		wait_init();
		owd::index_t vertex_positions_index = 0;
		owd::index_t vertices_index = 0;

		float delta_x = centre_x - m_centre.x;
		float delta_y = centre_y - m_centre.y;

		while (vertex_positions_index < m_vertex_positions.size())
		{
			m_vertex_positions[vertex_positions_index]     += delta_x;
			m_vertex_positions[vertex_positions_index + 1] += delta_y;

			m_vertices[vertices_index]     = m_vertex_positions[vertex_positions_index];
			m_vertices[vertices_index + 1] = m_vertex_positions[vertex_positions_index + 1];

			vertex_positions_index += 2;
			vertices_index += 6;
		}
		m_centre = { centre_x, centre_y };
		m_should_update = true;
	}

	void c_graphic_unit_lib::move(float delta_x, float delta_y)
	{
		wait_init();
		owd::index_t vertex_positions_index = 0;
		owd::index_t vertices_index = 0;

		while (vertex_positions_index < m_vertex_positions.size())
		{
			m_vertex_positions[vertex_positions_index] += delta_x;
			m_vertex_positions[vertex_positions_index + 1] += delta_y;

			m_vertices[vertices_index] = m_vertex_positions[vertex_positions_index];
			m_vertices[vertices_index + 1] = m_vertex_positions[vertex_positions_index + 1];

			vertex_positions_index += 2;
			vertices_index += 6;
		}
		m_centre = centre(m_vertex_positions, m_indices);
		m_should_update = true;
	}

	void c_graphic_unit_lib::resize(float size_multiplier)
	{
		wait_init();
		owd::index_t vertex_positions_index = 0;
		owd::index_t vertices_index = 0;

		while (vertex_positions_index < m_vertex_positions.size())
		{
			// Set to centre
			m_vertex_positions[vertex_positions_index]     -= m_centre.x;
			m_vertex_positions[vertex_positions_index + 1] -= m_centre.y;

			// Multiply
			m_vertex_positions[vertex_positions_index]     *= size_multiplier;
			m_vertex_positions[vertex_positions_index + 1] *= size_multiplier;

			// Move back
			m_vertex_positions[vertex_positions_index]     += m_centre.x;
			m_vertex_positions[vertex_positions_index + 1] += m_centre.y;

			m_vertices[vertices_index]     = m_vertex_positions[vertex_positions_index];
			m_vertices[vertices_index + 1] = m_vertex_positions[vertex_positions_index + 1];

			vertex_positions_index += 2;
			vertices_index += 6;
		}
		m_should_update = true;
	}

	void c_graphic_unit_lib::set_colour(float red, float green, float blue, float alpha)
	{
		wait_init();
		m_colour = { red, green, blue, alpha };

		owd::index_t vertex_positions_index = 0;
		owd::index_t vertices_index = 0;

		while (vertex_positions_index < m_vertex_positions.size())
		{
			m_vertices[vertices_index + 2] = red;
			m_vertices[vertices_index + 3] = green;
			m_vertices[vertices_index + 4] = blue;
			m_vertices[vertices_index + 5] = alpha;

			vertex_positions_index += 2;
			vertices_index += 6;
		}
		m_should_update = true;
	}

	gl_indices_t c_graphic_unit_lib::indices_batch(gl_index_t max_index)
	{
		gl_indices_t result = m_indices;
		// 0, 1, 0, 2,  0, 3,  0, 1
		// 4, 5, 4, 6,  4, 7,  4, 5
		// 8, 9, 8, 10, 8, 11, 8, 9
		gl_index_t increment = 0;
		if (max_index == 0)
		{
			increment = 0;
		}
		else
		{
			increment = max_index + 1;
		}
		for (owd::index_t i = 0; i != m_indices.size(); ++i)
		{
			result[i] += increment;
		}

		return result;
	}

	std::shared_ptr<c_graphic_unit_lib>& c_graphic_unit_lib::empty_unit()
	{
		return m_empty_unit;
	}

	owd::xy_t c_graphic_unit_lib::centre(const vertices_t& vertex_positions, const gl_indices_t& indices)
	{
		owd::xy_t result{ 0.0f, 0.0f };

		size_t indices_count = indices.size();

		for (owd::index_t i = 0; i < indices_count; ++i)
		{
			result += { vertex_positions[indices[i] * 2], vertex_positions[indices[i] * 2 + 1] };
		}

		result /= static_cast<float>(indices_count);

		return result;
	}
	bool c_graphic_unit_lib::wait_init()
	{
		std::mutex mtx{};
		return true;
		auto state = enm_state::not_init;
		while (true)
		{
			mtx.lock();
			{
				state = m_state;
				if (state == enm_state::deleted)
				{
					mtx.unlock();
					return false;
				}
				else if (state == enm_state::good)
				{
					mtx.unlock();
					break;
				}
			}
			mtx.unlock();
		}
		return true;
	}
}