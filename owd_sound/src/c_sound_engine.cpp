#include "c_sound_engine.h"

namespace owd_lib
{
	c_sound_engine* c_sound_engine::m_singleton = nullptr;

	void c_sound_engine::set_distance_model(enum_distance_model input)
	{
		m_distance_model.set_model(input);
	}

	//std::shared_ptr<c_listener>& c_sound_engine::listener()
	//{
	//	return m_listener_shared_ptr;
	//}

	/*void c_sound_engine::add_sound()
	{
		m_sound_bank.add();
	}*/

	void c_sound_engine::add_sound(const c_sound& other)
	{
		m_sound_bank.add(other);
	}

	void c_sound_engine::add_sound(std::shared_ptr<c_sound>& other)
	{
		m_sound_bank.add(other);
	}

	void c_sound_engine::load_sound(std::wstring_view filepath)
	{
		m_sound_bank.load(filepath);
	}

	void c_sound_engine::load_sound(std::wstring_view filepath, std::wstring_view name)
	{
		m_sound_bank.load(filepath, name);
	}

	std::shared_ptr<c_sound>& c_sound_engine::get_sound_by_index(index_t i)
	{
		return m_sound_bank.by_index(i);
	}

	std::shared_ptr<c_sound>& owd_lib::c_sound_engine::get_sound_by_name(std::wstring_view name)
	{
		return m_sound_bank.by_name(name);
	}

	std::shared_ptr<c_sound>& owd_lib::c_sound_engine::get_sound_by_filepath(std::wstring_view name)
	{
		return m_sound_bank.by_filepath(name);
	}

	void owd_lib::c_sound_engine::erase_sound_by_index(index_t i)
	{
		m_sound_bank.erase(i);
	}

	void owd_lib::c_sound_engine::erase_sound_by_name(std::wstring_view name)
	{
		m_sound_bank.erase(name);
	}

	void owd_lib::c_sound_engine::erase_sound_by_filepath(std::wstring_view filepath)
	{
		m_sound_bank.erase_by_filepath(filepath);
	}

	void c_sound_engine::clear_sounds()
	{
		m_sound_bank.clear();
	}

	void c_sound_engine::add_source(c_sound_source& other)
	{
		m_sound_source_bank.add(other);
	}

	void owd_lib::c_sound_engine::add_source(std::shared_ptr<c_sound_source>& other)
	{
		m_sound_source_bank.add(other);
	}

	std::shared_ptr<c_sound_source>& owd_lib::c_sound_engine::get_sound_source(index_t i)
	{
		return m_sound_source_bank.by_index(i);
	}

	std::shared_ptr<c_sound_source>& owd_lib::c_sound_engine::get_sound_source(std::wstring_view name)
	{
		return m_sound_source_bank.by_name(name);
	}
	
	void c_sound_engine::erase_source(std::wstring_view name)
	{
		return m_sound_source_bank.erase(name);
	}

	void c_sound_engine::erase_source(index_t index)
	{
		return m_sound_source_bank.erase(index);
	}

	void c_sound_engine::clear_sources()
	{
		m_sound_source_bank.clear();
	}

	void c_sound_engine::clear()
	{
		clear_sources();
		clear_sounds();
	}

	bool c_sound_engine::attach_sound(std::wstring_view sound_name, std::wstring_view source_name)
	{
		auto sound = get_sound_by_name(sound_name);

		if (sound->good())
		{
			auto source = get_sound_source(source_name);

			if (source->good())
			{
				return source->add_sound(sound);
			}
		}

		return false;
	}

	bool owd_lib::c_sound_engine::attach_sound(std::wstring_view sound_name, std::shared_ptr<c_sound_source>& sound_source)
	{
		auto sound = get_sound_by_name(sound_name);

		if (sound->good())
		{
			if (sound_source->good())
			{
				return sound_source->add_sound(sound);
			}
		}

		return false;
	}

	bool owd_lib::c_sound_engine::attach_sound(std::shared_ptr<c_sound>& sound, std::shared_ptr<c_sound_source>& sound_source)
	{
		if (sound->good())
		{
			if (sound_source->good())
			{
				return sound_source->add_sound(sound);
			}
		}

		return false;
	}

	bool owd_lib::c_sound_engine::attach_sound(std::shared_ptr<c_sound>& sound, std::wstring_view source_name)
	{
		if (sound->good())
		{
			auto source = get_sound_source(source_name);

			return source->add_sound(sound);
		}

		return false;
	}

	bool owd_lib::c_sound_engine::detach_sound(std::wstring_view sound_name, std::wstring_view source_name)
	{
		auto sound = get_sound_by_name(sound_name);

		if (sound->good())
		{
			auto source = get_sound_source(source_name);

			if (source->good())
			{
				return source->remove_sound(sound);
			}
		}

		return false;
	}

	bool owd_lib::c_sound_engine::detach_sound(std::wstring_view sound_name, std::shared_ptr<c_sound_source>& sound_source)
	{
		auto sound = get_sound_by_name(sound_name);

		if (sound->good())
		{
			if (sound_source->good())
			{
				return sound_source->remove_sound(sound);
			}
		}

		return false;
	}

	bool owd_lib::c_sound_engine::detach_sound(std::shared_ptr<c_sound>& sound, std::wstring_view source_name)
	{
		if (sound->good())
		{
			auto source = get_sound_source(source_name);

			if (source->good())
			{
				return source->remove_sound(sound);
			}
		}

		return false;
	}

	bool c_sound_engine::detach_sound(std::shared_ptr<c_sound>& sound, std::shared_ptr<c_sound_source>& sound_source)
	{
		if (sound->good())
		{
			if (sound_source->good())
			{
				return sound_source->remove_sound(sound);
			}
		}

		return false;
	}

	bool owd_lib::c_sound_engine::detach_sound(std::wstring_view source_name)
	{
		bool result = false;

		auto source = get_sound_source(source_name);

		if (source->good())
		{
			source->detach_all_sounds();
			result = true;
		}

		return result;
	}

	bool owd_lib::c_sound_engine::detach_sound(std::shared_ptr<c_sound_source>& sound_source)
	{
		bool result = false;

		if (sound_source->good())
		{
			sound_source->detach_all_sounds();
			result = true;
		}

		return result;
	}

	void c_sound_engine::detach_all()
	{
		for (index_t i = 0; i != m_sound_source_bank.count(); ++i)
		{
			m_sound_source_bank[i]->detach_all_sounds();
		}
	}

	c_sound_engine* owd_lib::c_sound_engine::get_instance()
	{
		if (m_singleton == nullptr)
		{
			m_singleton = new c_sound_engine();
		}

		return m_singleton;
	}
	void c_sound_engine::terminate()
	{
		if (m_singleton == nullptr)
		{

		}
		else
		{
			m_singleton->m_sound_bank.terminate();
			m_singleton->m_sound_source_bank.terminate();
			m_singleton->m_distance_model.terminate();
			m_singleton->m_listener.terminate();

			delete m_singleton;
			m_singleton = nullptr;
		}
	}
	c_sound_engine::c_sound_engine()
	{
		set_name(L"sound_engine");
		set_logger_name(L"sound_engine_logger");
		m_listener.set_position(0.0f, 0.0f, 0.0f);
		m_listener.set_gain(0.99f);
	}
	c_sound_engine::~c_sound_engine()
	{
	}

}

