#include "c_sound_bank.h"

namespace owd_lib
{
    using owd::index_t;
    using owd::strings_are_equal;
	c_sound_bank* c_sound_bank::m_singleton = nullptr;
    
    std::shared_ptr<c_sound_lib>& c_sound_bank::load(std::wstring_view filepath)
    {
        return load(filepath, filepath);
    }
    std::shared_ptr<c_sound_lib>& c_sound_bank::load(std::wstring_view filepath, std::wstring_view name)
    {

        auto file = std::make_shared<c_sound_lib>();
        this->m_logger << "----Loading file; filepath: " << filepath << "----\n";
        {
            if (this->m_vec_objects.empty())
            {

            }
            else
            {
                for (uint64_t i = 0; i != this->m_vec_objects.size(); ++i)
                {
                    if (strings_are_equal(this->m_vec_objects[i]->filepath(), filepath))
                    {
                        this->m_logger << "The filepath is already in the bank\n";
                        this->m_logger << "Loading ABORTED\n";

                        return this->m_vec_objects[i];
                    }
                    if (strings_are_equal(this->m_vec_objects[i]->name(), name))
                    {
                        this->m_logger << "The name is already in the bank\n";
                        this->m_logger << "Loading ABORTED\n";

                        return this->m_vec_objects[i];
                    }
                }
            }

            file->load(filepath, name);

            if (file->good())
            {
                file->set_name(name);
                this->m_vec_objects.push_back(file);
                this->m_logger << "Loading SUCCESS\n";
                return this->m_vec_objects.back();
            }
            else
            {
                this->m_logger << "Loading ERROR\n";
                return c_sound_lib::empty();
            }
        }

    }
    std::shared_ptr<c_sound_lib>& c_sound_bank::by_filepath(std::wstring_view filepath)
    {
        auto object = std::make_shared<c_sound_lib>();

        m_logger << "----Getting object by filepath: " << filepath << " START----\n";
        {
            if (m_vec_objects.empty())
            {
                m_logger << "ERROR: bank is empty\n";
            }
            else
            {
                bool found = false;

                for (owd::index_t i = 0; i != m_vec_objects.size(); ++i)
                {
                    if (strings_are_equal(this->m_vec_objects[i]->filepath(), filepath))
                    {
                        m_logger << "object found\n";
                        return m_vec_objects[i];
                        
                    }
                }
                if (found)
                {
                    m_logger << "object found\n";
                }
                else
                {
                    m_logger << "object NOT found\n";
                }
            }
        }
        m_logger << "----Getting object END----\n";

        return c_sound_lib::empty();
    }
    std::shared_ptr<c_sound_lib>& c_sound_bank::by_name(std::wstring_view name)
    {
        auto object = std::make_shared<c_sound_lib>();

        m_logger << "----Getting object by name: " << name << " START----\n";
        {
            if (m_vec_objects.empty())
            {
                m_logger << "ERROR: bank is empty\n";
            }
            else
            {
                bool found = false;

                for (owd::index_t i = 0; i != m_vec_objects.size(); ++i)
                {
                    if (strings_are_equal(this->m_vec_objects[i]->name(), name))
                    {
                        m_logger << "object found\n";
                        return m_vec_objects[i];

                    }
                }
                if (found)
                {
                    m_logger << "object found\n";
                }
                else
                {
                    m_logger << "object NOT found\n";
                }
            }
        }
        m_logger << "----Getting object END----\n";

        return c_sound_lib::empty();
    }
    void c_sound_bank::erase_by_filepath(std::wstring_view filepath)
    {
        m_logger << "----Erasing object by filepath: " << filepath << "----\n";
        {
            if (m_vec_objects.empty())
            {
                m_logger << "ERROR: bank is empty\n";
            }
            else
            {
                auto iter = m_vec_objects.begin();

                index_t index = 0;

                bool found = false;

                for (index_t i = 0; i != m_vec_objects.size(); ++i)
                {
                    if (strings_are_equal(this->m_vec_objects[i]->filepath(), filepath))
                    {
                        found = true;
                        break;
                    }
                    ++index;
                }
                if (found)
                {
                    m_logger << "object found\n";
                }
                else
                {
                    m_logger << "object NOT found\n";
                }

                iter += index;

                m_vec_objects.erase(iter);

                m_logger << "----Erasing object OK----\n";
            }
        }
        m_logger << "----Erasing object END----\n";
    }
	c_sound_bank* owd_lib::c_sound_bank::get_instance()
	{
		if (m_singleton == nullptr)
		{
			m_singleton = new c_sound_bank();
		}

		return m_singleton;
	}
	void c_sound_bank::terminate()
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
    c_sound_bank::c_sound_bank()
    {
    }
    c_sound_bank::~c_sound_bank()
    {
    }
}
