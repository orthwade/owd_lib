#pragma once
#include "c_sound_bank.h"
#include "c_sound_source_bank.h"
#include "c_listener.h"

namespace owd_lib
{
	class c_sound_engine : public c_basic_object
	{
	public:
		/// <summary>
		/// Sets model of attenuation depending on the distance between sound source and listener.
		/// 1. inverse_distance:
		/// gain = REFERENCE_DISTANCE / (REFERENCE_DISTANCE + ROLLOFF_FACTOR * (distance – REFERENCE_DISTANCE));
		//////
		/// 2. inverse_distance_clamped:
		/// distance = max(distance, REFERENCE_DISTANCE);
		/// distance = min(distance, MAX_DISTANCE);
		/// gain = REFERENCE_DISTANCE / (REFERENCE_DISTANCE +ROLLOFF_FACTOR *(distance – REFERENCE_DISTANCE));
		/// ///
		/// 3. linear_distance:
		/// distance = min(distance, MAX_DISTANCE) (avoid negative gain)
		/// gain = (1 – ROLLOFF_FACTOR * (distance – REFERENCE_DISTANCE) /(MAX_DISTANCE – REFERENCE_DISTANCE))
		/// ///
		/// 4. linear_distance_clamped:
		/// distance = max(distance, REFERENCE_DISTANCE)
		/// distance = min(distance, MAX_DISTANCE) 
		///	gain = (1 – ROLLOFF_FACTOR * (distance – REFERENCE_DISTANCE) / (MAX_DISTANCE – REFERENCE_DISTANCE))
		/// ///
		/// 5. exponent_distance:
		/// gain = (distance / REFERENCE_DISTANCE) ^ (-ROLLOFF_FACTOR)
		/// ///
		/// 6. exponent_distance_clamped:
		/// distance = max(distance, REFERENCE_DISTANCE) 
		/// distance = min(distance, MAX_DISTANCE) 
		/// gain = (distance / REFERENCE_DISTANCE) ^ (-ROLLOFF_FACTOR)
		/// ///
		/// 7. none:
		/// gain = 1
		/// /// 
		/// Default is inverse_distance_clamped
		/// </summary>
		/// <param name="input"></param>
		void set_distance_model(enum_distance_model input);

		///// <summary>
		///// Get listener shared pointer.
		///// </summary>
		///// <returns></returns>
		//std::shared_ptr<c_listener>& listener();

		inline c_listener& get_listener() { return m_listener; }

		/// <summary>
		/// Add blank sound to sound map
		/// </summary>
		//void add_sound();

		/// <summary>
		/// Add copy of other sound to sound map. 
		/// It will be an actual copy, except PCM data which is shared pointer, 
		/// [other] is suggested for deletion if not needed
		/// </summary>
		/// <param name="other"></param>
		void add_sound(const c_sound& other);

		/// <summary>
		/// Add other sound to sound map. 
		/// </summary>
		/// <param name="other"></param>
		void add_sound(std::shared_ptr<c_sound>& other);


		/// <summary>
		/// Add copy of other sound to sound map. 
		/// It will be an actual copy, except PCM data which is shared pointer, 
		/// other is suggested for deletion if not needed
		/// Avoid adding duplicates or sounds with the same name
		/// </summary>
		/// <param name="other"></param>
		//void add_sound(const c_sound* other);

		/// <summary>
		/// Add sound to sound map and load a file to it it. Name of the sound will be same file_path.
		/// Avoid adding duplicates or sounds with the same name
		/// </summary>
		/// <param name="file_path"></param>
		void load_sound(std::wstring_view file_path);

		/// <summary>
		/// Add sound to sound map, load a file to it it and attach a name to it.
		/// Avoid adding duplicates or sounds with the same name
		/// </summary>
		/// <param name="file_path"></param>
		/// <param name="name"></param>
		void load_sound(std::wstring_view file_path, std::wstring_view name);

		std::shared_ptr<c_sound>& get_sound_by_index(index_t i);
		std::shared_ptr<c_sound>& get_sound_by_name(std::wstring_view name);
		std::shared_ptr<c_sound>& get_sound_by_filepath(std::wstring_view name);

		void erase_sound_by_index(index_t i);
		void erase_sound_by_name(std::wstring_view name);
		void erase_sound_by_filepath(std::wstring_view name);

		/// <summary>
		/// Clear sound map.
		/// </summary>
		void clear_sounds();

		/// <summary>
		/// Add copy of other source to source map. 
		/// It will be an actual copy. Other is suggested for deletion if not needed
		/// Avoid adding duplicates or sources with the same name
		/// </summary>
		/// <param name="other"></param>
		void add_source(c_sound_source& const other);

		/// <summary>
		/// Add copy of other source to source map. 
		/// It will be an actual copy. Other is suggested for deletion if not needed.
		/// Avoid adding duplicates or sources with the same name
		/// </summary>
		/// <param name="other"></param>
		void add_source(std::shared_ptr<c_sound_source>& other);

		std::shared_ptr<c_sound_source>& get_sound_source(index_t i);
		std::shared_ptr<c_sound_source>& get_sound_source(std::wstring_view name);

		/// <summary>
		/// Delete source from a bank by name.
		/// </summary>
		/// <param name="name"></param>
		void erase_source(std::wstring_view name);

		/// <summary>
		/// Delete source from a bank by index.
		/// </summary>
		/// <param name="index"></param>
		void erase_source(index_t index);

		/// <summary>
		/// Clear source map.
		/// </summary>
		void clear_sources();

		/// <summary>
		/// Clear sound map and source map.
		/// </summary>
		void clear();

		/// <summary>
		/// Find sound by name in sound bank, find sound source in sound source bank,
		/// attach found sound to found sound source.
		/// </summary>
		/// <param name="sound_name"></param>
		/// <param name="source_name"></param>
		/// <returns></returns>
		bool attach_sound(std::wstring_view sound_name, std::wstring_view source_name);

		/// <summary>
		/// Find sound by name in sound bank and attach it to sound_source.
		/// </summary>
		/// <param name="sound_name"></param>
		/// <param name="sound_source"></param>
		/// <returns></returns>
		bool attach_sound(std::wstring_view sound_name, std::shared_ptr<c_sound_source>& sound_source);

		/// <summary>
		/// Find sound source in sound source bank and attach sound to it.
		/// </summary>
		/// <param name="sound"></param>
		/// <param name="source_name"></param>
		/// <returns></returns>
		bool attach_sound(std::shared_ptr<c_sound>& sound, std::wstring_view source_name);

		/// <summary>
		/// Attach sound to sound_source.
		/// </summary>
		/// <param name="sound_source"></param>
		/// <param name="source_name"></param>
		/// <returns></returns>
		bool attach_sound(std::shared_ptr<c_sound>& sound, std::shared_ptr<c_sound_source>& sound_source);
		
		/// <summary>
		/// Find sound by name in sound bank, find sound source in sound source bank,
		/// detach found sound from found sound source.
		/// </summary>
		/// <param name="sound_name"></param>
		/// <param name="source_name"></param>
		/// <returns></returns>
		bool detach_sound(std::wstring_view sound_name, std::wstring_view source_name);

		/// <summary>
		/// Find sound by name in sound bank and detach it from sound_source.
		/// </summary>
		/// <param name="sound_name"></param>
		/// <param name="sound_source"></param>
		/// <returns></returns>
		bool detach_sound(std::wstring_view sound_name, std::shared_ptr<c_sound_source>& sound_source);

		/// <summary>
		/// Find sound source in sound source bank and detach sound from it.
		/// </summary>
		/// <param name="sound"></param>
		/// <param name="source_name"></param>
		/// <returns></returns>
		bool detach_sound(std::shared_ptr<c_sound>& sound, std::wstring_view source_name);

		/// <summary>
		/// Detach sound from sound_source.
		/// </summary>
		/// <param name="sound_source"></param>
		/// <param name="source_name"></param>
		/// <returns></returns>
		bool detach_sound(std::shared_ptr<c_sound>& sound, std::shared_ptr<c_sound_source>& sound_source);

		/// <summary>
		/// Find sound source in sound source bank and detach all sounds from it.
		/// </summary>
		/// <param name="source_name"></param>
		/// <returns></returns>
		bool detach_sound(std::wstring_view source_name);

		/// <summary>
		/// Detach all sounds from sound_source.
		/// </summary>
		/// <param name="sound_source"></param>
		/// <returns></returns>
		bool detach_sound(std::shared_ptr<c_sound_source>& sound_source);

		/// <summary>
		/// Detach all sounds from all sources
		/// </summary>
		void detach_all();

		static c_sound_engine* get_instance();
		static void terminate();

	private:
		c_sound_bank* m_sound_bank_ptr = c_sound_bank::get_instance();
		c_sound_bank& m_sound_bank = *m_sound_bank_ptr;

		c_sound_source_bank* m_sound_source_bank_ptr = c_sound_source_bank::get_instance();
		c_sound_source_bank& m_sound_source_bank = *m_sound_source_bank_ptr;

		c_sound_distance_model* m_distance_model_ptr = c_sound_distance_model::get_instance();
		c_sound_distance_model& m_distance_model = *m_distance_model_ptr;

		c_listener* m_listener_ptr = c_listener::get_instance();
		c_listener& m_listener = *m_listener_ptr;

		static c_sound_engine* m_singleton;

		c_sound_engine();
		~c_sound_engine();

		c_sound_engine(const c_sound_engine&) = delete;
		c_sound_engine& operator=(const c_sound_engine&) = delete;
	};
}