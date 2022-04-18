#include "c_sound_source.h"
#include <owd_time.h>

namespace owd_lib
{
	using owd::strings_are_equal;

	c_sound_source_lib::c_sound_source_lib()
	{
		m_logger << m_name << '-' << "----source constructor START----\n";

		//m_openal_source_ptr = new ALuint;

		m_reference_distance	= (m_sound_distance_model_ptr->default_reference_distance()); 
		m_rolloff_factor		= (m_sound_distance_model_ptr->default_rolloff_factor()); 
		m_max_distance			= (m_sound_distance_model_ptr->default_max_distance()); 

		m_gain = 0.99f;

		m_logger << m_name << '-' << "----source constructor OK----\n";
	}
	c_sound_source_lib::c_sound_source_lib(std::wstring_view name)
	{
		m_logger << name << ' ' << "----source constructor START----\n";

		m_name = name;


		m_gain = 0.99f;

		m_reference_distance	= (m_sound_distance_model_ptr->default_reference_distance()); 
		m_rolloff_factor		= (m_sound_distance_model_ptr->default_rolloff_factor()); 
		m_max_distance			= (m_sound_distance_model_ptr->default_max_distance()); 

		m_logger << m_name << '-' << "----source constructor OK----\n";
	}
	c_sound_source_lib::c_sound_source_lib(std::wstring_view name, std::shared_ptr<c_sound_lib>& sound)
	{
		m_logger << name << ' ' << "----source constructor START----\n";

		m_name = name;

		m_gain = 0.99f;

		m_reference_distance	= (m_sound_distance_model_ptr->default_reference_distance()); 
		m_rolloff_factor		= (m_sound_distance_model_ptr->default_rolloff_factor()); 
		m_max_distance			= (m_sound_distance_model_ptr->default_max_distance()); 

		add_sound(sound);

		m_logger << m_name << '-' << "----source constructor OK----\n";
	}
	
	c_sound_source_lib::~c_sound_source_lib()
	{
	}

	void c_sound_source_lib::set_position(float x, float y, float z)
	{
		//m_mtx.lock();
		{
			m_logger << m_name << '-' 
				<< "setting position to all sounds x: " << x << ";    y: " << y << ";    z: " << z << '\n';

			m_x = x;
			m_y = y;
			m_z = z;

			if (m_vec_sounds.size() > 0)
			{
				for (auto iter = m_vec_sounds.begin(); iter != m_vec_sounds.end(); ++iter)
				{
					AL_CALL(alSource3f(*(iter->c), AL_POSITION, m_x, m_y, m_z));
				}
			}
		}
		//m_mtx.unlock();
	}

	void c_sound_source_lib::set_gain(float gain)
	{
		//m_mtx.lock();
		{
			m_logger << m_name << '-' << "setting gain to all sounds: " << gain << '\n';

			if (gain < 0.0f)
			{
				gain = 0.0f;
			}

			m_gain = gain;

			if (m_vec_sounds.size() > 0)
			{
				for (auto iter = m_vec_sounds.begin(); iter != m_vec_sounds.end(); ++iter)
				{
					AL_CALL(alSourcef(*(iter->c), AL_GAIN, gain));
				}
			}
			else
			{
				m_logger << m_name << '-' << "!: sound vector empty\n";
			}
		}
		//m_mtx.unlock();
	}

	void c_sound_source_lib::set_gain(c_sound_lib* sound, float gain)
	{
		//m_mtx.lock();
		{
			m_logger << m_name << '-' << "setting gain to [" << sound->name() << "]: " << gain << '\n';

			if (gain < 0.0f)
			{
				gain = 0.0f;
			}

			m_gain = gain;

			if (m_vec_sounds.size() > 0)
			{
				bool found = false;
				for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
				{
					if (m_vec_sounds.at(i).s.get() == sound)
					{
						AL_CALL(alSourcef(*(m_vec_sounds.at(i).c), AL_GAIN, gain));
						found = true;
						break;
					}
				}
				if (!found)
				{
					m_logger << m_name << '-' << "ERROR: sound [" << sound->name() << "] not found\n";
				}
			}
			else
			{
				m_logger << m_name << '-' << "!: sound vector empty\n";
			}
		}
		//m_mtx.unlock();
	}

	void c_sound_source_lib::set_gain(std::wstring_view name, float gain)
	{
		std::wstring name_str = std::wstring(name);
		//m_mtx.lock();
		{
			m_logger << m_name << '-' << "setting gain to [" << name_str << "]: " << gain << '\n';

			if (gain < 0.0f)
			{
				gain = 0.0f;
			}

			m_gain = gain;

			if (m_vec_sounds.size() > 0)
			{
				bool found = false;
				for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
				{
					if (strings_are_equal(m_vec_sounds.at(i).s->name(), name_str))
					{
						AL_CALL(alSourcef(*(m_vec_sounds.at(i).c), AL_GAIN, gain));
						found = true;
						break;
					}
				}
				if (!found)
				{
					m_logger << m_name << '-' << "ERROR: sound [" << name_str << "] not found\n";
				}
			}
			else
			{
				m_logger << m_name << '-' << "!: sound vector empty\n";
			}
		}
		//m_mtx.unlock();
	}

	void c_sound_source_lib::set_velocity(float x, float y, float z)
	{
		//m_mtx.lock();
		{
			m_logger << m_name << '-' << "setting velocity x: " << x << ";    y: " << y << ";    z: " << z << '\n';
			m_velocity_x = x;
			m_velocity_y = y;
			m_velocity_z = z;

			if (m_vec_sounds.size() > 0)
			{
				for (auto iter = m_vec_sounds.begin(); iter != m_vec_sounds.end(); ++iter)
				{
					AL_CALL(alSource3f(*(iter->c), AL_VELOCITY, x, y, z));
				}
			}
			else
			{
				m_logger << m_name << '-' << "!: sound vector empty\n";
			}
		}
		//m_mtx.unlock();
	}

	void c_sound_source_lib::set_reference_distance(float input)
	{

		//m_mtx.lock();
		{
			m_logger << m_name << '-' << "setting reference distance: " << input << '\n';

			if (input < 0.0f)
			{
				input = 0.0f;
			}

			m_reference_distance = input;

			if (m_vec_sounds.size() > 0)
			{
				for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
				{
					AL_CALL(alSourcef(*(m_vec_sounds.at(i).c), AL_REFERENCE_DISTANCE, m_reference_distance));
				}
			}
			else
			{
				m_logger << m_name << '-' << "!: sound vector empty\n";
			}
		}
		//m_mtx.unlock();
	}

	void c_sound_source_lib::set_rolloff_factor(float input)
	{
		m_logger << m_name << '-' << "setting rolloff factor: " << input << '\n';

		//m_mtx.lock();
		{
			if (input < 0.0f)
			{
				input = 0.0f;
			}

			m_rolloff_factor = input;

			if (m_vec_sounds.size() > 0)
			{
				for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
				{
					AL_CALL(alSourcef(*(m_vec_sounds.at(i).c), AL_ROLLOFF_FACTOR, m_rolloff_factor));
				}
			}
			else
			{
				m_logger << m_name << '-' << "!: sound vector empty\n";
			}
		}
		//m_mtx.unlock();
	}

	void c_sound_source_lib::set_max_distance(float input)
	{
		//m_mtx.lock();
		{
			m_logger << m_name << '-' << "setting max distance: " << input << '\n';

			if (input < 0.0f)
			{
				input = 0.0f;
			}

			m_max_distance = input;

			if (m_vec_sounds.size() > 0)
			{
				for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
				{
					AL_CALL(alSourcef(*(m_vec_sounds.at(i).c), AL_MAX_DISTANCE, m_max_distance));
				}
			}
			else
			{
				m_logger << m_name << '-' << "!: sound vector empty\n";
			}
		}
		//m_mtx.unlock();

		//areturn result;
	}

	owd::xyz_t c_sound_source_lib::get_position()
	{
		owd::xyz_t result{};

		//m_mtx.lock();
		{
			result = { m_x, m_y, m_z };
		}
		//m_mtx.unlock();

		return result;
	}

	float c_sound_source_lib::get_gain()
	{
		float result{};

		//m_mtx.lock();
		{
			result = m_gain;
		}
		//m_mtx.unlock();

		return result;
	}

	float c_sound_source_lib::get_gain(c_sound_lib* sound)
	{
		float result{};

		//m_mtx.lock();
		{
			bool found = false;
			if (sound != nullptr)
			{
				for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
				{
					if (m_vec_sounds.at(i).s.get() == sound)
					{
						AL_CALL(alGetSourcef(*(m_vec_sounds.at(i).c), AL_GAIN, &result));
						found = true;
						break;
					}
				}
				if (!found)
				{
					m_logger << m_name << '-' << "ERROR: sound [" << sound->name() << "] not found\n";
				}
			}
			else
			{
				m_logger << m_name << '-' << "ERROR: input sound is nullptr\n";
			}
		}
		//m_mtx.unlock();

		return result;
	}

	float c_sound_source_lib::get_gain(std::wstring_view name)
	{
		float result{};

		//m_mtx.lock();
		{
			bool found = false;
			for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
			{
				if (strings_are_equal(m_vec_sounds.at(i).s->name(), name))
				{
					AL_CALL(alGetSourcef(*(m_vec_sounds.at(i).c), AL_GAIN, &result));
					found = true;
					break;
				}
			}
			if (!found)
			{
				m_logger << m_name << '-' << "ERROR: sound [" << name << "] not found\n";
			}
		}
		//m_mtx.unlock();

		return result;
	}

	bool c_sound_source_lib::enable()
	{
		bool result = true;

		//m_mtx.lock();
		{
			m_logger << m_name << '-' << "Playing all sounds\n";
			if (m_vec_sounds.size() > 0)
			{
				for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
				{
					AL_CALL(alSourcePlay(*(m_vec_sounds.at(i).c)););
				}
			}
			else
			{
				m_logger << m_name << '-' << "ERROR: sound vector empty\n";
			}
		}
		//m_mtx.unlock();

		return result;
	}

	bool c_sound_source_lib::pause()
	{
		bool result = true;

		//m_mtx.lock();
		{
			m_logger << m_name << '-' << "Pausing all sounds\n";
			if (m_vec_sounds.size() > 0)
			{
				for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
				{
					AL_CALL(alSourcePause(*(m_vec_sounds.at(i).c)));
				}
			}
			else
			{
				m_logger << m_name << '-' << "ERROR: sound vector empty\n";
			}
		}
		//m_mtx.unlock();

		return result;
	}

	bool c_sound_source_lib::stop()
	{
		bool result = true;

		//m_mtx.lock();
		{
			m_logger << m_name << '-' << "Stopping all sounds\n";
			if (m_vec_sounds.size() > 0)
			{
				for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
				{
					AL_CALL(alSourceStop(*(m_vec_sounds.at(i).c)));
				}
			}
			else
			{
				m_logger << m_name << '-' << "ERROR: sound vector empty\n";
			}
		}
		//m_mtx.unlock();

		return result;
	}

	bool c_sound_source_lib::enable(std::shared_ptr<c_sound_lib>& sound_ptr)
	{
		bool result = true;

		//m_mtx.lock();
		{
			if (m_vec_sounds.size() > 0)
			{
				if (sound_ptr != nullptr)
				{
					bool found = false;
					m_logger << m_name << '-' << "Playing sound: " << sound_ptr->name() << "\n";
					for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
					{
						if (m_vec_sounds.at(i).s.get() == sound_ptr.get())
						{
							found = true;
							AL_CALL(alSourcePlay(*(m_vec_sounds.at(i).c)));
							break;
						}
						
					}
					if (!found)
					{
						m_logger << m_name << '-' << "ERROR: sound not found\n";
					}
				}
				else
				{
					m_logger << m_name << '-' << "ERROR: input sound pointer is nullptr\n";
				}
			}
			else
			{
				m_logger << m_name << '-' << "ERROR: sound vector empty\n";
			}
		}
		//m_mtx.unlock();

		return result;
	}

	bool c_sound_source_lib::pause(std::shared_ptr<c_sound_lib>& sound_ptr)
	{
		bool result = true;

		//m_mtx.lock();
		{
			if (m_vec_sounds.size() > 0)
			{
				if (sound_ptr != nullptr)
				{
					bool found = false;
					m_logger << m_name << '-' << "Pausing sound: " << sound_ptr->name() << "\n";
					for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
					{
						if (m_vec_sounds.at(i).s.get() == sound_ptr.get())
						{
							found = true;
							AL_CALL(alSourcePause(*(m_vec_sounds.at(i).c)));
							break;
						}
					}
					if (!found)
					{
						m_logger << m_name << '-' << "ERROR: sound not found\n";
					}
				}
				else
				{
					m_logger << m_name << '-' << "ERROR: input sound pointer is nullptr\n";
				}
			}
			else
			{
				m_logger << m_name << '-' << "ERROR: sound vector empty\n";
			}
		}
		//m_mtx.unlock();

		return result;
	}

	bool c_sound_source_lib::stop(std::shared_ptr<c_sound_lib>& sound_ptr)
	{
		bool result = true;

		//m_mtx.lock();
		{
			if (m_vec_sounds.size() > 0)
			{
				if (sound_ptr != nullptr)
				{
					bool found = false;
					m_logger << m_name << '-' << "Stopping sound: " << sound_ptr->name() << "\n";
					for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
					{
						if (m_vec_sounds.at(i).s.get() == sound_ptr.get())
						{
							found = true;
							AL_CALL(alSourceStop(*(m_vec_sounds.at(i).c)));
							break;
						}
					}
					if (!found)
					{
						m_logger << m_name << '-' << "ERROR: sound not found\n";
					}
				}
				else
				{
					m_logger << m_name << '-' << "ERROR: input sound pointer is nullptr\n";
				}
			}
			else
			{
				m_logger << m_name << '-' << "ERROR: sound vector empty\n";
			}
		}
		//m_mtx.unlock();

		return result;
	}

	bool c_sound_source_lib::enable(std::vector<std::shared_ptr<c_sound_lib>> vec_sound_ptr)
	{
		bool result = true;

		//m_mtx.lock();
		{
			if (m_vec_sounds.size() > 0)
			{
				if (vec_sound_ptr.size() > 0)
				{
					bool found = false;
					for (uint16_t n = 0; n != vec_sound_ptr.size(); ++n)
					{
						if (vec_sound_ptr.at(n) != nullptr)
						{
							found = false;
							m_logger << m_name << '-' << "Playing sound: " << vec_sound_ptr.at(n)->name() << "\n";
							for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
							{

								if (m_vec_sounds.at(i).s.get() == vec_sound_ptr.at(n).get())
								{
									found = true;
									AL_CALL(alSourcePlay(*(m_vec_sounds.at(i).c)));
									break;
								}
							}
							if (!found)
							{
								m_logger << m_name << '-' << "ERROR: sound not found\n";
							}
						}
						else
						{
							m_logger << m_name << '-' << "ERROR: input sound pointer is nullptr\n";
						}
					}
				}
				else
				{
					m_logger << m_name << '-' << "ERROR: input sound vector empty\n";
				}
			}
			else
			{
				m_logger << m_name << '-' << "ERROR: sound vector empty\n";
			}
		}
		//m_mtx.unlock();

		return result;
	}
	
	bool c_sound_source_lib::pause(std::vector<std::shared_ptr<c_sound_lib>> vec_sound_ptr)
	{
		bool result = true;

		//m_mtx.lock();
		{
			if (m_vec_sounds.size() > 0)
			{
				if (vec_sound_ptr.size() > 0)
				{
					
					bool found = false;
					for (uint16_t n = 0; n != vec_sound_ptr.size(); ++n)
					{
						if (vec_sound_ptr.at(n) != nullptr)
						{
							found = false;
							m_logger << m_name << '-' << "Pausing sound: " << vec_sound_ptr.at(n)->name() << "\n";
							for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
							{
								if (m_vec_sounds.at(i).s.get() == vec_sound_ptr.at(n).get())
								{
									found = true;
									AL_CALL(alSourcePause(*(m_vec_sounds.at(i).c)));
									break;
								}
							}
							if (!found)
							{
								m_logger << m_name << '-' << "ERROR: sound not found\n";
							}
						}
						else
						{
							m_logger << m_name << '-' << "ERROR: input sound pointer is nullptr\n";
						}
					}
				}
				else
				{
					m_logger << m_name << '-' << "ERROR: input sound vector empty\n";
				}
			}
			else
			{
				m_logger << m_name << '-' << "ERROR: sound vector empty\n";
			}
		}
		//m_mtx.unlock();

		return result;
	}

	bool c_sound_source_lib::stop(std::vector<std::shared_ptr<c_sound_lib>> vec_sound_ptr)
	{
		bool result = true;

		//m_mtx.lock();
		{
			if (m_vec_sounds.size() > 0)
			{
				if (vec_sound_ptr.size() > 0)
				{
					bool found = false;
					for (uint16_t n = 0; n != vec_sound_ptr.size(); ++n)
					{
						if (vec_sound_ptr.at(n) != nullptr)
						{
							found = false;
							m_logger << m_name << '-' << "Stopping sound: " << vec_sound_ptr.at(n)->name() << "\n";
							for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
							{
								if (m_vec_sounds.at(i).s.get() == vec_sound_ptr.at(n).get())
								{
									found = true;
									AL_CALL(alSourceStop(*(m_vec_sounds.at(i).c)));
									break;
								}
							}
							if (!found)
							{
								m_logger << m_name << '-' << "ERROR: sound not found\n";
							}
						}
						else
						{
							m_logger << m_name << '-' << "ERROR: input sound pointer is nullptr\n";
						}
					}
				}
				else
				{
					m_logger << m_name << '-' << "ERROR: input sound vector empty\n";
				}
			}
			else
			{
				m_logger << m_name << '-' << "ERROR: sound vector empty\n";
			}
		}
		//m_mtx.unlock();

		return result;
	}

	bool c_sound_source_lib::enable_by_name(std::wstring_view name)
	{
		bool result = true;

		//m_mtx.lock();
		{
			if (m_vec_sounds.size() > 0)
			{
				bool found = false;
				m_logger << m_name << '-' << "Playing sound: " << name << "\n";
				for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
				{
					if (strings_are_equal(m_vec_sounds.at(i).s->name(), name))
					{
						found = true;
						AL_CALL(alSourcePlay(*(m_vec_sounds.at(i).c)));
						break;
					}
					if (!found)
					{
						m_logger << m_name << '-' << "ERROR: sound not found\n";
					}
				}
			}
			else
			{
				m_logger << m_name << '-' << "ERROR: sound vector empty\n";
			}
		}
		//m_mtx.unlock();

		return result;
	}

	bool c_sound_source_lib::pause_by_name(std::wstring_view name)
	{
		bool result = true;

		//m_mtx.lock();
		{
			if (m_vec_sounds.size() > 0)
			{
				bool found = false;
				m_logger << m_name << '-' << "Pausing sound: " << name << "\n";
				for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
				{
					if (strings_are_equal(m_vec_sounds.at(i).s->name(), name))
					{
						found = true;
						AL_CALL(alSourcePause(*(m_vec_sounds.at(i).c)));
						break;
					}
					if (!found)
					{
						m_logger << m_name << '-' << "ERROR: sound not found\n";
					}
				}
			}
			else
			{
				m_logger << m_name << '-' << "ERROR: sound vector empty\n";
			}
		}
		//m_mtx.unlock();

		return result;
	}

	bool c_sound_source_lib::stop_by_name(std::wstring_view name)
	{
		bool result = true;

		//m_mtx.lock();
		{
			if (m_vec_sounds.size() > 0)
			{
				bool found = false;
				m_logger << m_name << '-' << "Stopping sound: " << name << "\n";
				for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
				{
					if (strings_are_equal(m_vec_sounds.at(i).s->name(), name))
					{
						found = true;
						AL_CALL(alSourceStop(*(m_vec_sounds.at(i).c)));
						break;
					}
					if (!found)
					{
						m_logger << m_name << '-' << "ERROR: sound not found\n";
					}
				}
			}
			else
			{
				m_logger << m_name << '-' << "ERROR: sound vector empty\n";
			}
		}
		//m_mtx.unlock();

		return result;
	}

	bool c_sound_source_lib::enable_by_name(std::vector<std::wstring_view> vec_names)
	{
		bool result = true;

		//m_mtx.lock();
		{
			if (m_vec_sounds.size() > 0)
			{
				if (vec_names.size() > 0)
				{
					bool found = false;
					for (uint16_t n = 0; n != vec_names.size(); ++n)
					{
						found = false;
						m_logger << m_name << '-' << "Playing sound: " << vec_names.at(n) << "\n";
						for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
						{
							if (strings_are_equal(m_vec_sounds.at(i).s->name(), vec_names.at(n)))
							{

								found = true;
								AL_CALL(alSourcePlay(*(m_vec_sounds.at(i).c)));
								break;
							}
							if (!found)
							{
								m_logger << m_name << '-' << "ERROR: sound not found\n";
							}
						}
					}
				}
				else
				{
					m_logger << m_name << '-' << "ERROR: input name vector empty\n";
				}
			}
			else
			{
				m_logger << m_name << '-' << "ERROR: sound vector empty\n";
			}
		}
		//m_mtx.unlock();

		return result;
	}

	bool c_sound_source_lib::pause_by_name(std::vector<std::wstring_view> vec_names)
	{
		bool result = true;

		//m_mtx.lock();
		{
			if (m_vec_sounds.size() > 0)
			{
				if (vec_names.size() > 0)
				{
					bool found = false;
					for (uint16_t n = 0; n != vec_names.size(); ++n)
					{
						found = false;
						m_logger << m_name << '-' << "Pausing sound: " << vec_names.at(n) << "\n";
						for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
						{
							if (strings_are_equal(m_vec_sounds.at(i).s->name(), vec_names.at(n)))
							{
								found = true;
								AL_CALL(alSourcePause(*(m_vec_sounds.at(i).c)));
								break;
							}
							if (!found)
							{
								m_logger << m_name << '-' << "ERROR: sound not found\n";
							}
						}
					}
				}
				else
				{
					m_logger << m_name << '-' << "ERROR: input name vector empty\n";
				}
			}
			else
			{
				m_logger << m_name << '-' << "ERROR: sound vector empty\n";
			}
		}
		//m_mtx.unlock();

		return result;
	}

	bool c_sound_source_lib::stop_by_name(std::vector<std::wstring_view> vec_names)
	{
		bool result = true;

		//m_mtx.lock();
		{
			if (m_vec_sounds.size() > 0)
			{
				if (vec_names.size() > 0)
				{
					bool found = false;
					for (uint16_t n = 0; n != vec_names.size(); ++n)
					{
						found = false;
						m_logger << m_name << '-' << "Stopping sound: " << vec_names.at(n) << "\n";
						for (uint16_t i = 0; i != m_vec_sounds.size(); ++i)
						{
							if (strings_are_equal(m_vec_sounds.at(i).s->name(), vec_names.at(n)))
							{
								found = true;
								AL_CALL(alSourceStop(*(m_vec_sounds.at(i).c)));
								break;
							}
							if (!found)
							{
								m_logger << m_name << '-' << "ERROR: sound not found\n";
							}
						}
					}
				}
				else
				{
					m_logger << m_name << '-' << "ERROR: input name vector empty\n";
				}
			}
			else
			{
				m_logger << m_name << '-' << "ERROR: sound vector empty\n";
			}
		}
		//m_mtx.unlock();

		return result;
	}

	bool c_sound_source_lib::add_sound(std::shared_ptr<c_sound_lib>& sound)
	{
		bool result = false;
		//m_mtx.lock();
		{
			m_logger << m_name << '-' << "Adding sound: " << sound->name() << '\n';
			if (sound->good())
			{
				m_vec_sounds.push_back({ sound, (sound->buffer()->openal_buffer()) });

				AL_CALL(alGenSources(1, m_vec_sounds.back().c));

				AL_CALL(alSourcei(*(m_vec_sounds.back().c), AL_BUFFER, (m_vec_sounds.back().b)));

				AL_CALL(alSourcef(*(m_vec_sounds.back().c), AL_REFERENCE_DISTANCE, m_reference_distance));

				AL_CALL(alSourcef(*(m_vec_sounds.back().c), AL_ROLLOFF_FACTOR, m_rolloff_factor));

				AL_CALL(alSourcef(*(m_vec_sounds.back().c), AL_MAX_DISTANCE, m_max_distance));

				AL_CALL(alSourcef(*(m_vec_sounds.back().c), AL_GAIN, m_gain));

				result = true;
			}
			else
			{
				m_logger << m_name << '-' << "sound is not OK\n";
			}
		}
		//m_mtx.unlock();
		return result;
	}

	bool c_sound_source_lib::remove_sound(std::shared_ptr<c_sound_lib>& sound)
	{
		bool result = false;
		//m_mtx.lock();
		{
			m_logger << m_name << '-' << "Removing sound: " << sound->name() << '\n';

			bool found = false;
			for (auto iter = m_vec_sounds.begin(); iter != m_vec_sounds.end(); ++iter)
			{
				if (sound.get() == iter->s.get())
				{
					m_vec_sounds.erase(iter);
					//alSourceUnqueueBuffers(*m_openal_source_ptr, 1, sound->buffer()->openal_buffer());
					//m_openal_check(L"alSourceUnqueueBuffers");
					found = true;
					result = true;
					break;
				}
			}
			if (found)
			{

			}
			else
			{
				m_logger << m_name << '-' << "Removing sound ERROR: sound not found\n";
			}
		}
		//m_mtx.unlock();
		return result;
	}

	bool c_sound_source_lib::remove_sound(std::vector<c_sound_lib*> vec_sound_ptr)
	{
		bool result = true;
		bool found = false;

		c_sound_lib* sound_ptr = nullptr;

		//m_mtx.lock();
		{
			if (vec_sound_ptr.size() > 0)
			{
				for (uint16_t i = 0; i != vec_sound_ptr.size(); ++i)
				{
					sound_ptr = vec_sound_ptr.at(i);
					if (sound_ptr != nullptr)
					{
						m_logger << m_name << '-' << "Removing sound: " << sound_ptr->name() << '\n';

						for (auto iter = m_vec_sounds.begin(); iter != m_vec_sounds.end(); ++iter)
						{
							if (sound_ptr == iter->s.get())
							{
								m_vec_sounds.erase(iter);
								//alSourceUnqueueBuffers(*m_openal_source_ptr, 1, sound->buffer()->openal_buffer());
								//m_openal_check(L"alSourceUnqueueBuffers");
								found = true;
								break;
							}
						}
						if (found)
						{

						}
						else
						{
							m_logger << m_name << '-' << "Removing sound ERROR: sound not found\n";
							result = false;
						}
					}
					else
					{
						result = false;
					}
				}
			}
			else
			{
				result = false;
			}

			
			
		}
		//m_mtx.unlock();
		return result;
	}

	bool c_sound_source_lib::remove_sound_by_name(std::wstring_view name)
	{
		bool result = false;
		//m_mtx.lock();
		{
			m_logger << m_name << '-' << "Removing sound: " << name << '\n';

			bool found = false;
			for (auto iter = m_vec_sounds.begin(); iter != m_vec_sounds.end(); ++iter)
			{
				if (name == iter->s->name())
				{
					m_vec_sounds.erase(iter);
					//alSourceUnqueueBuffers(*m_openal_source_ptr, 1, sound->buffer()->openal_buffer());
					//m_openal_check(L"alSourceUnqueueBuffers");
					found = true;
					result = true;
					break;
				}
			}
			if (found)
			{

			}
			else
			{
				m_logger << m_name << '-' << "Removing sound ERROR: sound not found\n";
			}
		}
		//m_mtx.unlock();
		return result;
	}

	bool c_sound_source_lib::remove_sound_by_name(std::vector<std::wstring_view> vec_names)
	{
		bool result = true;
		bool found = false;

		//c_sound* sound_ptr = nullptr;

		//m_mtx.lock();
		{
			if (vec_names.size() > 0)
			{
				for (uint16_t i = 0; i != vec_names.size(); ++i)
				{
					m_logger << m_name << '-' << "Removing sound: " << vec_names.at(i) << '\n';

					for (auto iter = m_vec_sounds.begin(); iter != m_vec_sounds.end(); ++iter)
					{
						if (vec_names.at(i) == iter->s->name())
						{
							m_vec_sounds.erase(iter);
							//alSourceUnqueueBuffers(*m_openal_source_ptr, 1, sound->buffer()->openal_buffer());
							//m_openal_check(L"alSourceUnqueueBuffers");
							found = true;
							break;
						}
					}
					if (found)
					{

					}
					else
					{
						m_logger << m_name << '-' << "Removing sound ERROR: sound not found\n";
						result = false;
					}
				}
			}
			else
			{
				result = false;
			}
		}
		//m_mtx.unlock();
		return result;
	}

	void c_sound_source_lib::detach_all_sounds()
	{
		//m_mtx.lock();
		{
			m_logger << m_name << '-' << "Removing all sounds\n";
			m_vec_sounds.clear();
		}
		//m_mtx.unlock();
	}

	
	s_sound_::s_sound_(std::shared_ptr<c_sound_lib>& in_s, ALuint in_b)
		:s_sound_(in_s, in_b, 0)
	{
		//s = std::make_shared<c_sound>(in_s);
		//b = in_b;

	}

	s_sound_::s_sound_(std::shared_ptr<c_sound_lib>& in_s, ALuint in_b, ALuint in_c)
		:
		s(in_s),
		b(in_b),
		c(new ALuint(in_c))
	{
		//s = std::make_shared<c_sound>(in_s);
		//b = in_b;
		//c = std::make_shared<ALuint>();
		//*c = *in_c;
	}

	s_sound_::~s_sound_()
	{

	}
}