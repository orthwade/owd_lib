#include "c_sound_distance_model.h"

namespace owd_lib
{
	c_sound_distance_model* c_sound_distance_model::m_singleton = nullptr;

	static constexpr enum_distance_model_lib inverse_distance_ = enum_distance_model_lib::inverse_distance;
	static constexpr enum_distance_model_lib inverse_distance_clamped_ = enum_distance_model_lib::inverse_distance_clamped;
	static constexpr enum_distance_model_lib linear_distance_ = enum_distance_model_lib::linear_distance;
	static constexpr enum_distance_model_lib linear_distance_clamped_ = enum_distance_model_lib::linear_distance_clamped;
	static constexpr enum_distance_model_lib exponent_distance_ = enum_distance_model_lib::exponent_distance;
	static constexpr enum_distance_model_lib exponent_distance_clamped_ = enum_distance_model_lib::exponent_distance_clamped;
	static constexpr enum_distance_model_lib none_ = enum_distance_model_lib::none;

	void c_sound_distance_model::set_model(ALenum input)
	{
		m_logger << "Setting distance model. Distance model int code: " << input << '\n';

		//m_mtx.lock();
		{
			m_model = input;
			switch (input)
			{
			case AL_INVERSE_DISTANCE:
				m_logger << "Setting distance model [AL_INVERSE_DISTANCE]\n";
				break;

			case AL_INVERSE_DISTANCE_CLAMPED:
				m_logger << "Setting distance model [AL_INVERSE_DISTANCE_CLAMPED]\n";
				break;

			case AL_LINEAR_DISTANCE:
				m_logger << "Setting distance model [AL_LINEAR_DISTANCE]\n";
				break;

			case AL_LINEAR_DISTANCE_CLAMPED:
				m_logger << "Setting distance model [AL_LINEAR_DISTANCE_CLAMPED]\n";
				break;

			case AL_EXPONENT_DISTANCE:
				m_logger << "Setting distance model [AL_EXPONENT_DISTANCE]\n";
				break;

			case AL_EXPONENT_DISTANCE_CLAMPED:
				m_logger << "Setting distance model [AL_EXPONENT_DISTANCE_CLAMPED]\n";
				break;

			case AL_NONE:
				m_logger << "Setting distance model [AL_NONE]\n";
				break;

			default:
				m_logger << "Unknown distance model. Distance model is set to [AL_NONE]\n";
				m_model = AL_NONE;
				break;
			}
			AL_CALL(alDistanceModel(m_model));
		}
		//m_mtx.unlock();
	}

	void c_sound_distance_model::set_model(enum_distance_model_lib input)
	{
		switch (input)
		{
		case	inverse_distance_:				set_model(AL_INVERSE_DISTANCE);	break;
		case	inverse_distance_clamped_:		set_model(AL_INVERSE_DISTANCE_CLAMPED);	break;
		case	linear_distance_:				set_model(AL_LINEAR_DISTANCE);	break;
		case	linear_distance_clamped_:		set_model(AL_LINEAR_DISTANCE_CLAMPED);	break;
		case	exponent_distance_:				set_model(AL_EXPONENT_DISTANCE);	break;
		case	exponent_distance_clamped_:		set_model(AL_EXPONENT_DISTANCE_CLAMPED);	break;
		case	none_:							set_model(AL_NONE);	break;
		}
	}

	void c_sound_distance_model::set_default_reference_distance(float input)
	{
		m_logger << "Setting default reference distance: " << input << '\n';

		//m_mtx.lock();
		{
			if (input < 0.0f)
			{
				input = 0.0f;
			}
			m_reference_distance = input;
		}
		//m_mtx.unlock();
	}

	void c_sound_distance_model::set_default_rolloff_factor(float input)
	{
		m_logger << "Setting default rolloff factor: " << input << '\n';

		//m_mtx.lock();
		{
			if (input < 0.0f)
			{
				input = 0.0f;
			}
			m_rolloff_factor = input;
		}
		//m_mtx.unlock();
	}

	void c_sound_distance_model::set_default_max_distance(float input)
	{
		m_logger << "Setting default max distance: " << input << '\n';

		//m_mtx.lock();
		{
			if (input < 0.0f)
			{
				input = 0.0f;
			}
			m_max_distance = input;
		}
		//m_mtx.unlock();
	}

	float c_sound_distance_model::default_reference_distance()
	{
		return m_reference_distance;
	}

	float c_sound_distance_model::default_rolloff_factor()
	{
		return m_rolloff_factor;
	}

	float c_sound_distance_model::default_max_distance()
	{
		return m_max_distance;
	}

	c_sound_distance_model* c_sound_distance_model::get_instance()
	{
		if (m_singleton == nullptr)
		{
			m_singleton = new c_sound_distance_model();
		}

		return m_singleton;
	}
	void c_sound_distance_model::terminate()
	{
		if (m_singleton == nullptr)
		{

		}
		else
		{
			delete m_singleton;
			m_singleton = nullptr;
		}
	}
    c_sound_distance_model::c_sound_distance_model()
    {
		set_name(L"sound_distance_model");
		m_logger.set_name(L"sound_distance_model_logger");
		set_model(AL_INVERSE_DISTANCE_CLAMPED);
		set_default_reference_distance(1.0f);
		set_default_rolloff_factor(1.0f);
		set_default_max_distance(10.0f);
    }
}
