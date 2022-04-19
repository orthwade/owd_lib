#include "owd_sound_.h"
#include "../src/c_listener.h"
#include "../src/c_sound_bank.h"
#include "../src/c_sound_source.h"
#include "../src/c_sound_distance_model.h"

owd_lib::c_sound_distance_model* static_sound_distance_model = owd_lib::c_sound_distance_model::get_instance();
owd::c_listener* owd::c_listener::m_singleton = nullptr;

static owd_lib::c_listener_lib* static_listener_lib = nullptr;
static owd_lib::c_sound_bank* static_sound_bank = owd_lib::c_sound_bank::get_instance();
static owd_lib::c_sound_source_lib* sound_source_lib(void* m_data) 
{
	return reinterpret_cast<owd_lib::c_sound_source_lib*>(m_data);
}

static owd_lib::enum_distance_model_lib convert_sound_distance_model(uint8_t input)
{
	owd_lib::enum_distance_model_lib result = owd_lib::enum_distance_model_lib::inverse_distance_clamped;
	switch (input)
	{
		case uint8_t(0): owd_lib::enum_distance_model_lib::inverse_distance		    ; break;
		case uint8_t(2): owd_lib::enum_distance_model_lib::linear_distance		    ; break;
		case uint8_t(3): owd_lib::enum_distance_model_lib::linear_distance_clamped  ; break;
		case uint8_t(4): owd_lib::enum_distance_model_lib::exponent_distance		; break;
		case uint8_t(5): owd_lib::enum_distance_model_lib::exponent_distance_clamped; break;
		case uint8_t(6): owd_lib::enum_distance_model_lib::none						; break;
		default:
			break;
	}
	return result;
}

namespace owd
{
	void c_listener::set_position(float x, float y, float z)
	{
		static_listener_lib->set_position(x, y, z);
	}

	void c_listener::set_gain(float gain)
	{
		static_listener_lib->set_gain(gain);
	}

	void c_listener::set_velocity(float x, float y, float z)
	{
		static_listener_lib->set_velocity(x, y, z);
	}

	owd::xyz_t c_listener::position()
	{
		return static_listener_lib->position();
	}

	owd::xyz_t c_listener::orientation_at()
	{
		return static_listener_lib->orientation_at();
	}

	owd::xyz_t c_listener::orientation_up()
	{
		return static_listener_lib->orientation_up();
	}

	owd::ori_t c_listener::orientation()
	{
		return static_listener_lib->orientation();
	}

	void c_listener::rotate(float v, float h, float r)
	{
		static_listener_lib->rotate(v, h, r);
	}

	void c_listener::rotate_(float v, float h, float r)
	{
		static_listener_lib->rotate_(v, h, r);
	}

	void c_listener::set_default_orientation()
	{
		static_listener_lib->set_default_orientation();
	}

	float c_listener::gain()
	{
		return static_listener_lib->gain();
	}

	c_listener* c_listener::get_instance()
	{
		static_listener_lib = owd_lib::c_listener_lib::get_instance();

		if (m_singleton == nullptr)
		{
			m_singleton = new c_listener();
		}

		return m_singleton;
	}

	void c_listener::terminate()
	{
		if (m_singleton == nullptr)
		{
		}
		else
		{
			delete m_singleton;
			m_singleton = nullptr;
		}
		static_listener_lib->terminate();
	}

	c_listener::c_listener()
	{
	}

	c_sound_source::c_sound_source(std::wstring_view name)
		:
		m_data(new owd_lib::c_sound_source_lib(name))
	{
		auto distance_model = owd_lib::c_sound_distance_model::get_instance();
	}

	c_sound_source::~c_sound_source()
	{
		delete sound_source_lib(m_data);
	}

	std::wstring_view c_sound_source::name()
	{
		return sound_source_lib(m_data)->name();
	}

	void c_sound_source::load_sound(std::wstring_view filepath, std::wstring_view name)
	{
		auto sound = static_sound_bank->load(filepath, name);
		sound_source_lib(m_data)->add_sound(sound);
	}

	void c_sound_source::add_sound(std::wstring_view sound_name)
	{
		auto sound = static_sound_bank->by_name(sound_name);
		sound_source_lib(m_data)->add_sound(sound);
	}

	void c_sound_source::enable()
	{
		sound_source_lib(m_data)->enable();
	}

	void c_sound_source::pause()
	{
		sound_source_lib(m_data)->pause();
	}

	void c_sound_source::stop()
	{
		sound_source_lib(m_data)->stop();
	}

	void c_sound_source::enable(std::vector<std::wstring_view> vec_sound_name)
	{
		sound_source_lib(m_data)->enable_by_name(vec_sound_name);
	}

	void c_sound_source::pause(std::vector<std::wstring_view> vec_sound_name)
	{
		sound_source_lib(m_data)->pause_by_name(vec_sound_name);
	}

	void c_sound_source::stop(std::vector<std::wstring_view> vec_sound_name)
	{
		sound_source_lib(m_data)->stop_by_name(vec_sound_name);
	}

	void c_sound_source::set_position(float x, float y, float z)
	{
		sound_source_lib(m_data)->set_position(x, y, z);
	}

	void c_sound_source::set_gain(float gain)
	{
		sound_source_lib(m_data)->set_gain(gain);
	}

	void c_sound_source::set_gain(std::wstring_view sound_name, float gain)
	{
		sound_source_lib(m_data)->set_gain(sound_name, gain);
	}

	void c_sound_source::set_reference_distance(float input)
	{
		sound_source_lib(m_data)->set_reference_distance(input);
	}

	void c_sound_source::set_rolloff_factor(float input)
	{
		sound_source_lib(m_data)->set_rolloff_factor(input);
	}

	void c_sound_source::set_max_distance(float input)
	{
		sound_source_lib(m_data)->set_max_distance(input);
	}

	void c_sound_source::detach_sound(std::wstring_view sound_name)
	{
		sound_source_lib(m_data)->remove_sound_by_name(sound_name);
	}

	void c_sound_source::detach_all()
	{
		sound_source_lib(m_data)->detach_all_sounds();
	}

	void load_sound(std::wstring_view filepath, std::wstring_view name)
	{
		static_sound_bank->load(filepath, name);
	}

	bool check_sound_by_name(std::wstring_view name)
	{
		return static_sound_bank->by_name(name)->good();
	}

	bool check_sound_by_filepath(std::wstring_view filepath)
	{
		return static_sound_bank->by_filepath(filepath)->good();
	}

	/*void set_sound_distance_model(enum_distance_model input)
	{
		static_sound_distance_model->set_model()
	}*/

	void set_sound_distance_model(uint8_t input)
	{
		static_sound_distance_model->set_model(convert_sound_distance_model(input));
	}

	void set_sound_default_reference_distance(float input)
	{
		static_sound_distance_model->set_default_reference_distance(input);
	}

	void set_sound_default_rolloff_factor(float input)
	{
		static_sound_distance_model->set_default_rolloff_factor(input);
	}

	void set_sound_default_max_distance(float input)
	{
		static_sound_distance_model->set_default_max_distance(input);
	}

	float default_sound_reference_distance()
	{
		return 0.0f;
	}

	float default_sound_rolloff_factor()
	{
		return 0.0f;
	}

	float default_sound_max_distance()
	{
		return 0.0f;
	}

}