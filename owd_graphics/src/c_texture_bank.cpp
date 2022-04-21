#include "c_texture_bank.h"

namespace owd_lib
{
	c_texture_bank* c_texture_bank::m_singleton = nullptr;

	c_texture_bank* c_texture_bank::get_instance()
	{
		if (m_singleton == nullptr)
		{
			m_singleton = new c_texture_bank();
		}

		return m_singleton;
	}
	void c_texture_bank::terminate()
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
	bool c_texture_bank::load(std::wstring_view filepath, std::wstring_view name)
	{
		wait_update();
		std::lock_guard lock(m_mtx);
		m_list_buffer.push_back({ std::wstring(filepath), std::wstring(name) });
		m_should_update.store(true);
		return true;
	}
	bool c_texture_bank::erase(std::wstring_view name)
	{
		wait_update();
		std::lock_guard lock(m_mtx);
		m_list_erase.push_back(std::wstring(name));
		m_should_update.store(true);
		return true;
	}
	texture_t& c_texture_bank::get(std::wstring_view name)
	{
		wait_update();

		std::lock_guard lock(m_mtx);
		if (this->m_vec_objects.empty())
		{
		}
		else
		{
			for (uint64_t i = 0; i != this->m_vec_objects.size(); ++i)
			{
				if (owd::strings_are_equal(this->m_vec_objects[i]->name(), name))
				{
					return this->m_vec_objects[i];
				}
			}
		}

		return m_empty_object;
	}
	void c_texture_bank::update_main_thread()
	{
		std::lock_guard lock{ m_mtx };
		if (!m_list_buffer.empty())
		{
			m_should_update.store(true);

			for (auto& element : m_list_buffer)
			{
				bool result = false;

				auto file = std::make_shared<c_texture>();
				this->m_logger << "----Loading file; filepath: " << element.filepath << "----\n";
				{
					if (this->m_vec_objects.empty())
					{

					}
					else
					{
						for (uint64_t i = 0; i != this->m_vec_objects.size(); ++i)
						{
							if (owd::strings_are_equal(this->m_vec_objects[i]->filepath(), element.filepath))
							{
								this->m_logger << "The filepath is already in the bank\n";
								this->m_logger << "Loading ABORTED\n";
							}
							if (owd::strings_are_equal(this->m_vec_objects[i]->name(), element.name))
							{
								this->m_logger << "The name is already in the bank\n";
								this->m_logger << "Loading ABORTED\n";
							}
						}
					}

					result = file->load(element.filepath, element.name);

					if (result)
					{
						this->m_vec_objects.push_back(file);

						this->m_logger << "Loading SUCCESS\n";
					}
					else
					{
						this->m_logger << "Loading ERROR\n";
					}
				}
				this->m_logger << "----Loading file END----\n";

			}

			m_list_buffer.clear();
		}
		if(!m_list_erase.empty())
		{
			m_should_update.store(true);
			for (auto& element : m_list_erase)
			{
				c_file_bank::erase_by_name(element);
			}
		}
		m_should_update.store(false);
	}
	void c_texture_bank::wait_update()
	{
		while (m_should_update)
		{

		}
	}
	c_texture_bank::c_texture_bank()
	{
	}
	c_texture_bank::~c_texture_bank()
	{
	}
}
