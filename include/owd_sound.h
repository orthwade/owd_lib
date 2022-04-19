#pragma once
#include <owd_misc.h>

namespace owd
{
	constexpr uint8_t inverse_distance_sound_model			= 0;
	constexpr uint8_t inverse_distance_clamped_sound_model	= 1;
	constexpr uint8_t linear_distance_sound_model			= 2;
	constexpr uint8_t linear_distance_clamped_sound_model	= 3;
	constexpr uint8_t exponent_distance_sound_model			= 4;
	constexpr uint8_t exponent_distance_clamped_sound_model	= 5;
	constexpr uint8_t none_distance_sound_model				= 6;

	void set_sound_distance_model(uint8_t input);

	void set_sound_default_reference_distance	(float input);
	void set_sound_default_rolloff_factor		(float input);
	void set_sound_default_max_distance			(float input);

	float default_sound_reference_distance();
	float default_sound_rolloff_factor();
	float default_sound_max_distance();

	class c_listener
	{
	public:
		void set_position(float x, float y, float z);

		void set_gain(float gain);
		void set_velocity(float x, float y, float z);

		owd::xyz_t position();

		owd::xyz_t orientation_at();
		owd::xyz_t orientation_up();
		owd::ori_t orientation();

		/// <summary>
		/// Rotate orientation around OX', OY' or OZ' axes.
		/// OX', OY', OZ' do not necessarily match original axes OX, OY, OZ.
		/// OX' in general is the axis perpendicular both to AT and UP vectors(codirectional 
		/// with cross product of UP and AT vectors).
		/// OY' in general is the axis codirectional with UP vector.
		/// OZ' in general is the axis codirectional with AT vector.
		/// </summary>
		/// <param name="v">Angle in degrees to rotate orientation around OX' axis(vertical rotation).</param>
		/// <param name="h">Angle in degrees to rotate orientation around OY' axis(horizontal rotation)</param>
		/// <param name="r">Angle in degrees to rotate orientation around OZ' axis(roll)</param>
		void rotate(float v, float h, float r);

		/// <summary>
		/// Rotate vectors AT and UP around original axes OX, OY, OZ.
		/// </summary>
		/// <param name="v">Angle in degrees to rotate vectors AT and UP around OX axis</param>
		/// <param name="h">Angle in degrees to rotate vectors AT and UP around OY axis</param>
		/// <param name="r">Angle in degrees to rotate vectors AT and UP around OZ axis</param>
		void rotate_(float v, float h, float r);

		void set_default_orientation();

		float gain();

		static c_listener* get_instance();
		static void terminate();

	private:
		static c_listener* m_singleton;

		c_listener();
	};

	void load_sound(std::wstring_view filepath, std::wstring_view name);
	bool check_sound_by_name(std::wstring_view name);
	bool check_sound_by_filepath(std::wstring_view filepath);

	class c_sound_source
	{
	public:
		c_sound_source(std::wstring_view name);
		~c_sound_source();

		std::wstring_view name();

		void load_sound(std::wstring_view filepath, std::wstring_view name);
		void add_sound(std::wstring_view sound_name);

		void enable();
		void pause();
		void stop();

		void enable	(std::vector<std::wstring_view> vec_sound_name);
		void pause	(std::vector<std::wstring_view> vec_sound_name);
		void stop	(std::vector<std::wstring_view> vec_sound_name);

		void set_position(float x, float y, float z);
		void set_gain(float gain);

		void set_gain(std::wstring_view sound_name, float gain);

		void set_reference_distance	(float input);
		void set_rolloff_factor		(float input);
		void set_max_distance		(float input);

		void detach_sound(std::wstring_view sound_name);
		void detach_all();

	private:
		void* m_data;
	};

};