#pragma once
#include "c_openal_object.h"

namespace owd_lib
{
	enum class enum_distance_model
	{
		inverse_distance,
		inverse_distance_clamped,
		linear_distance,
		linear_distance_clamped,
		exponent_distance,
		exponent_distance_clamped,
		none
	};

	class c_sound_distance_model : public c_openal_object
	{
	public:
		void set_model(ALenum input);
		void set_model(enum_distance_model input);

		void set_default_reference_distance(float input);
		void set_default_rolloff_factor(float input);
		void set_default_max_distance(float input);

		float default_reference_distance();
		float default_rolloff_factor();
		float default_max_distance();

		static c_sound_distance_model* get_instance();
		void terminate();

	private:
		ALenum m_model{};

		float m_reference_distance{};
		float m_rolloff_factor{};
		float m_max_distance{};

		static c_sound_distance_model* m_singleton;

		c_sound_distance_model();

		//c_sound_distance_model(const c_sound_distance_model&) = delete;
		//c_sound_distance_model& operator=(const c_sound_distance_model&) = delete;
	};
}