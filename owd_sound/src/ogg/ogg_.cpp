#include "ogg_.h"





namespace owd_lib
{

	static size_t read(void* buffer, size_t element_size, size_t element_count, void* data_source) 
	{
		assert(element_size == 1);

		std::ifstream& stream = *static_cast<std::ifstream*>(data_source);
		stream.read(static_cast<char*>(buffer), element_count);
		const std::streamsize bytes_read = stream.gcount();
		stream.clear(); // In case we read past EOF
		return static_cast<size_t>(bytes_read);
	}

	static int seek(void* data_source, ogg_int64_t offset, int origin) 
	{
		static const std::vector<std::ios_base::seekdir> seek_directions
		{
			std::ios_base::beg, std::ios_base::cur, std::ios_base::end
		};

		std::ifstream& stream = *static_cast<std::ifstream*>(data_source);
		stream.seekg(offset, seek_directions.at(origin));
		stream.clear(); // In case we seeked to EOF
		return 0;
	}

	static long tell(void* data_source) 
	{
		std::ifstream& stream = *static_cast<std::ifstream*>(data_source);
		const auto position = stream.tellg();
		assert(position >= 0);
		return static_cast<long>(position);
	}

	static const ov_callbacks callbacks{ read, seek, nullptr, tell };

	c_ogg_file::c_ogg_file()
		
	{
		m_logger << "----ogg_file constructor START----\n";
		set_logger_name(L"ogg_file_object_logger");
		set_name(L"ogg_file_object");
		m_logger << "----ogg_file constructor OK----\n";
	}
	
	c_ogg_file::~c_ogg_file()
	{
		m_logger << "----ogg_file destructor START----\n";
		//delete[] m_sound_data_ptr;
		m_logger << "----ogg_file destructor OK----\n";
	}

	bool c_ogg_file::load(std::wstring_view filepath)
	{
		return load(filepath, filepath);
	}
	bool c_ogg_file::load(std::wstring_view filepath, std::wstring_view name)
	{
		set_name(name);
		m_filepath = (filepath);

		m_logger << "loading file: " << m_filepath << '\n';

		//m_mtx.lock();
		{
			m_ifstream().open(m_filepath, std::ios::binary);

			if (m_ifstream().is_open())
			{
				m_logger << "file open OK\n";
			}
			else
			{
				m_logger << "file open ERROR\n";
				m_state = enm_state::error;
				return false;
			}

			OggVorbis_File ogg_vorbis_file{};

			vorbis_info* vorbis_info_ = nullptr;

			if (ov_open_callbacks(&m_ifstream, &ogg_vorbis_file, nullptr, 0, callbacks) < 0)
			{
				m_logger << "ov_open_callbacks ERROR\n";
				m_state = enm_state::error;
				//m_mtx.unlock();
				return false;
			}
			else
			{
				m_logger << "ov_open_callbacks OK\n";
			}

			vorbis_info_ = ov_info(&ogg_vorbis_file, -1);

			m_samples_count = ov_pcm_total(&ogg_vorbis_file, -1);
			m_channels_count = vorbis_info_->channels;
			m_sample_rate = vorbis_info_->rate;
			m_bits_per_sample = 16;
			m_sound_data_bytes_count = m_bits_per_sample / 8 * m_samples_count * m_channels_count + 4096;

			//auto ii = std::make_shared<int>(new int[3]);

			m_data_shared_ptr->resize(m_sound_data_bytes_count);
			m_sound_data_ptr = m_data_shared_ptr->data();
			m_sound_data_ptr_start_position = m_sound_data_ptr;

			int32_t current_section;
			int32_t end_of_file = 0;
			int64_t read_bytes_count{};
			int64_t total_read_bytes_count{};

			auto sound_data_char_ptr = reinterpret_cast<char*>(m_sound_data_ptr);

			while (!end_of_file)
			{
				read_bytes_count =
					ov_read(&ogg_vorbis_file, sound_data_char_ptr, 4096, 0, m_bits_per_sample / 8, 1, &current_section);
				if (read_bytes_count == 0)
				{
					end_of_file = 1;
					break;
				}
				else if (read_bytes_count < 0)
				{

				}
				else
				{
					total_read_bytes_count += read_bytes_count;
					m_sound_data_ptr += read_bytes_count;
				}
			}
			m_sound_data_bytes_count = total_read_bytes_count;

			m_sound_data_ptr = m_sound_data_ptr_start_position;
			//m_sound_data_ptr -= total_read_bytes_count;
			m_ifstream().close();
			ov_clear(&ogg_vorbis_file);
			m_logger << "loading file OK\n";
			m_state = enm_state::good;
		}
		//m_mtx.unlock();

		return true;
	}
	void c_ogg_file::reset()
	{
		*this = c_ogg_file();
	}
}