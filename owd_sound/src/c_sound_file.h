#pragma once
#include "../filesystem/c_file.h"

namespace owd_lib
{
	class c_sound_file : public c_file
	{
	public:
		c_sound_file();
		c_sound_file(std::wstring_view name);

		inline	size_t		samples_count			() { return m_samples_count				; }
		inline	uint32_t	channels_count			() { return m_channels_count			; }
		inline	uint32_t	sample_rate				() { return m_sample_rate				; }
		inline	uint32_t	bits_per_sample			() { return m_bits_per_sample			; }
		inline	uint32_t	sound_data_bytes_count	() { return m_sound_data_bytes_count	; }

		virtual inline	byte_t* sound_data_ptr() = 0;

	protected:
		size_t		m_samples_count{};
		uint32_t	m_channels_count{};
		uint32_t	m_sample_rate{};
		uint32_t	m_bits_per_sample{};
		uint32_t	m_sound_data_bytes_count{};
	};
}