#include "c_sound.h"

namespace owd_lib
{
	std::shared_ptr<c_sound_lib> c_sound_lib::m_empty_sound = std::make_shared<c_sound_lib>();
	//std::shared_ptr<c_sound_lib> c_sound_lib::m_empty_sound{ nullptr };
	static auto static_set_empty_sound_bad = [&]() 
	{ c_sound_lib::empty()->set_bad(); c_sound_lib::empty()->set_name(L"empty_sound"); return uint8_t(); };
	static auto static_set_empty_sound_bad_result = static_set_empty_sound_bad();

	c_sound_lib::c_sound_lib()
	{
		set_name(L"sound_object");
		m_logger.set_name(L"sound_object_logger");
	}
	
	c_sound_lib::~c_sound_lib()
	{
		if (m_sound_buffer != nullptr)
		{
			m_sound_buffer->release();
			delete m_sound_buffer;
			m_sound_buffer = nullptr;
		}
	}

	bool c_sound_lib::load(std::wstring_view filepath)
	{
		return load(filepath, filepath);
	}
	bool c_sound_lib::load(std::wstring_view filepath, std::wstring_view name)
	{
		m_name = name;
		m_logger << m_name << '-' << "loading file: " << filepath << '\n';

		//m_ogg.load(filepath, name);

		if (m_ogg.load(filepath))
		{
			m_good = m_set_data();
		}

		return m_good;
	}
	c_sound_buffer* c_sound_lib::buffer()
	{
		return m_sound_buffer;
	}

	bool c_sound_lib::good() const
	{
		return m_good;
	}

	bool c_sound_lib::m_set_data()
	{
		bool result = false;
		ALenum format{};

		if (channels_count() == 1)
		{
			if (bits_per_sample() == 8)
			{
				format = AL_FORMAT_MONO8;
			}
			else if (bits_per_sample() == 16)
			{
				format = AL_FORMAT_MONO16;
			}
		}
		else if (channels_count() == 2)
		{
			if (bits_per_sample() == 8)
			{
				format = AL_FORMAT_STEREO8;
			}
			else if (bits_per_sample() == 16)
			{
				format = AL_FORMAT_STEREO16;
			}
		}

		if (format == ALenum{})
		{
			m_logger << "----ERROR: Unsupporter format----\n";
		}
		else
		{
			result = true;
			if (m_sound_buffer == nullptr)
			{
				m_sound_buffer = new c_sound_buffer();
			}
			m_sound_buffer->set_data(sound_data_ptr(), sound_data_bytes_count(), sample_rate(), format);
		}

		return result;
	}
}