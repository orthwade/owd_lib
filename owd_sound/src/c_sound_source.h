#pragma once
#include <array>
#include "c_sound.h"
#include "c_sound_distance_model.h"

namespace owd_lib
{
	struct s_sound_
	{
		s_sound_(std::shared_ptr<c_sound_lib>& in_s, ALuint in_b);
		s_sound_(std::shared_ptr<c_sound_lib>& in_s, ALuint in_b, ALuint in_c);
		~s_sound_();

		// sound_ptr
		std::shared_ptr<c_sound_lib> s = std::make_shared<c_sound_lib>();
	
		// openal_buffer
		ALuint b{};

		// openal_source
		ALuint* c = nullptr;
	};

	class c_sound_source_lib : public owd::c_basic_object
	{
	public:
		c_sound_source_lib();
		c_sound_source_lib(std::wstring_view name);
		c_sound_source_lib(std::wstring_view name, std::shared_ptr<c_sound_lib>& sound);

		~c_sound_source_lib();

		void set_position(float x, float y, float z);
		void set_gain(float gain);
		void set_gain(c_sound_lib* sound,			float gain);
		void set_gain(std::wstring_view name,	float gain);
		void set_velocity(float x, float y, float z);

		void set_reference_distance	(float input);
		void set_rolloff_factor		(float input);
		void set_max_distance		(float input);

		owd::xyz_t get_position();

		float get_gain();
		float get_gain(c_sound_lib* sound);
		float get_gain(std::wstring_view name);

		bool enable	();
		bool pause	();
		bool stop	();

		bool enable	(std::shared_ptr<c_sound_lib>& sound_ptr);
		bool pause	(std::shared_ptr<c_sound_lib>& sound_ptr);
		bool stop	(std::shared_ptr<c_sound_lib>& sound_ptr);

		bool enable	(std::vector<std::shared_ptr<c_sound_lib>> vec_sound_ptr);
		bool pause	(std::vector<std::shared_ptr<c_sound_lib>> vec_sound_ptr);
		bool stop	(std::vector<std::shared_ptr<c_sound_lib>> vec_sound_ptr);

		bool enable_by_name	(std::wstring_view name);
		bool pause_by_name	(std::wstring_view name);
		bool stop_by_name	(std::wstring_view name);

		bool enable_by_name	(std::vector<std::wstring_view> vec_names);
		bool pause_by_name	(std::vector<std::wstring_view> vec_names);
		bool stop_by_name	(std::vector<std::wstring_view> vec_names);

		bool add_sound(std::shared_ptr<c_sound_lib>& sound);

		bool remove_sound(std::shared_ptr<c_sound_lib>& sound);
		bool remove_sound(std::vector<c_sound_lib*> vec_sound_ptr);
		bool remove_sound_by_name(std::wstring_view name);
		bool remove_sound_by_name(std::vector<std::wstring_view> vec_names);

		void detach_all_sounds();

	private:
		//std::vector<c_sound*> m_vec_sounds{};
		std::vector<s_sound_> m_vec_sounds{};
		c_sound_distance_model* m_sound_distance_model_ptr = c_sound_distance_model::get_instance();

		float m_x{};
		float m_y{};
		float m_z{};

		float m_gain{};

		float m_velocity_x{};
		float m_velocity_y{};
		float m_velocity_z{};

		float m_reference_distance{};
		float m_rolloff_factor{};
		float m_max_distance{};

	};
}