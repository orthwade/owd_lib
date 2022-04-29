#include "owd_graphics_.h"
#include "../src/c_graphic_engine.h"



static auto static_graphic_engine	= owd_lib::c_graphic_engine	::get_instance();
static auto static_texture_bank		= owd_lib::c_texture_bank	::get_instance();
static auto static_batch_handler	= owd_lib::c_batch_handler	::get_instance();

static owd_lib::c_graphic_unit_lib* lib_coloured(void* data)
{
	return reinterpret_cast<owd_lib::c_graphic_unit_lib*>(data);
}
static owd_lib::c_graphic_unit_textured* lib_textured(void* data)
{
	return reinterpret_cast<owd_lib::c_graphic_unit_textured*>(data);
}

namespace owd
{
	c_graphic_unit::c_graphic_unit(const std::vector<float>& positions, const std::vector<uint32_t>& indices,
		float r, float g, float b, float a, uint16_t l)
		:
		m_type(coloured_unit),
		m_data(static_batch_handler->add(positions, indices, r, g, b, a, l))
	{
	}
	c_graphic_unit::c_graphic_unit
	(float x, float y, float w, float h, float r, float g, float b, float a, uint16_t l)
		:
		m_type(coloured_unit),
		m_data(static_batch_handler->add(x, y, w, h, r, g, b, a, l))
	{
	}

	c_graphic_unit::c_graphic_unit(float x, float y, float radius, float r, float g, float b, float a, uint16_t l)
		:
		m_type(coloured_unit),
		m_data(static_batch_handler->add(x, y, radius, r, g, b, a, l))
	{
	}

	c_graphic_unit::c_graphic_unit(float x, float y, float w, float h, std::wstring_view t, uint16_t l)
		:
		m_type(textured_unit),
		m_data(static_batch_handler->add(x, y, w, h, t, l))
	{
	}

	c_graphic_unit::~c_graphic_unit()
	{
		if (m_type == coloured_unit)
		{
			reinterpret_cast<owd_lib::c_graphic_unit_lib*>(m_data)->set_to_delete();
		}
		else
		{
			reinterpret_cast<owd_lib::c_graphic_unit_textured*>(m_data)->set_to_delete();
		}
	}

	enm_graphic_unit c_graphic_unit::type()
	{
		return m_type;
	}

	float c_graphic_unit::x()
	{
		if (m_type == coloured_unit)
		{
			return lib_coloured(m_data)->centre().x;
		}
		else
		{
			return lib_textured(m_data)->centre().x;
		}
	}

	float c_graphic_unit::y()
	{
		if (m_type == coloured_unit)
		{
			return lib_coloured(m_data)->centre().y;
		}
		else
		{
			return lib_textured(m_data)->centre().y;
		}
	}

	void c_graphic_unit::resize(float multiplier)
	{
		if (m_type == coloured_unit)
		{
			lib_coloured(m_data)->resize(multiplier);
		}
		else
		{
			lib_textured(m_data)->resize(multiplier);
		}
	}

	void c_graphic_unit::set_position(float x, float y)
	{
		if (m_type == coloured_unit)
		{
			lib_coloured(m_data)->set_position(x, y);
		}
		else
		{
			lib_textured(m_data)->set_position(x, y);
		}
	}

	void c_graphic_unit::move(float d_x, float d_y)
	{
		if (m_type == coloured_unit)
		{
			lib_coloured(m_data)->move(d_x, d_y);
		}
		else
		{
			lib_textured(m_data)->move(d_x, d_y);
		}
	}

	void run()
	{
		auto static_graphic_engine = owd_lib::c_graphic_engine::get_instance();
		static_graphic_engine->run();
	}
	void terminate()
	{
		static_graphic_engine->terminate();
	}
	void load_texture(std::wstring_view filepath, std::wstring_view name)
	{
		static_texture_bank->load(filepath, name);
	}

	void remove_texture(std::wstring_view name)
	{
		static_texture_bank->erase_by_name(name);
	}

	void clear_textures()
	{
		static_texture_bank->clear();
	}

	void set_entities_wait()
	{
		static_graphic_engine->set_entities_wait();
	}

	void set_entities_ready()
	{
		static_graphic_engine->set_entities_ready();
	}

	void update_window()
	{
		static_graphic_engine->update_window();
	}

	bool window_should_close()
	{
		return static_graphic_engine->window_should_close();
	}

	void wait_frame()
	{
		static_graphic_engine->wait_frame();
	}

	float fps()
	{
		return static_graphic_engine->fps();
	}


}