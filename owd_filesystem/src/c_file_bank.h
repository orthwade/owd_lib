#pragma once
#include "c_file.h"
#include "../misc/c_object_bank.h"

namespace owd_lib
{
    template <class T>
    class c_file_bank : public c_object_bank<T>
    {
    public:
        c_file_bank();
        c_file_bank(std::wstring_view name);

        ~c_file_bank();

        bool load(std::wstring_view filepath);
        bool load(std::wstring_view filepath, std::wstring_view name);

        std::shared_ptr<T>& load_and_get(std::wstring_view filepath);

        std::shared_ptr<T>& by_filepath(std::wstring_view filepath);

        void erase_by_filepath(std::wstring_view name);

    protected:

    };

    template<class T>
    c_file_bank<T>::c_file_bank()
    {
    }

    template<class T>
    c_file_bank<T>::c_file_bank(std::wstring_view name)
    {
    }

    template<class T>
    c_file_bank<T>::~c_file_bank()
    {
    }

    template<class T>
    bool c_file_bank<T>::load(std::wstring_view filepath)
    {
        return load(filepath, filepath);
    }
    template<class T>
    bool owd_lib::c_file_bank<T>::load(std::wstring_view filepath, std::wstring_view name)
    {
        bool result = false;

        auto file = std::make_shared<T>();
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

                        return false;
                    }
                    if (strings_are_equal(this->m_vec_objects[i]->name(), name))
                    {
                        this->m_logger << "The name is already in the bank\n";
                        this->m_logger << "Loading ABORTED\n";

                        return false;
                    }
                }
            }

            result = file->load(filepath, name);

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

        return result;
    }

    template<class T>
    std::shared_ptr<T>& c_file_bank<T>::load_and_get(std::wstring_view filepath)
    {
        auto file = std::make_shared<T>();
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
                }
            }

            if (file->load(filepath))
            {
                this->m_vec_objects.push_back(file);
                this->m_logger << "Loading SUCCESS\n";
                return this->m_vec_objects.back();
            }
            else
            {
                this->m_logger << "Loading ERROR\n";
            }
        }
        this->m_logger << "----Loading file END----\n";

        return file;
    }


    template<class T>
    std::shared_ptr<T>& c_file_bank<T>::by_filepath(std::wstring_view filepath)
    {
        auto file = std::make_shared<T>();

        this->m_logger << "----Getting file by filepath: " << filepath << " START----\n";
        {
            if (this->m_vec_objects.empty())
            {
                this->m_logger << "ERROR: bank is empty\n";
            }
            else
            {
                bool found = false;
                for (uint64_t i = 0; i != this->m_vec_objects.size(); ++i)
                {
                    if (strings_are_equal(this->m_vec_objects[i]->filepath(), filepath))
                    {
                        file = this->m_vec_objects[i];
                        found = true;
                    }
                }
                if (found)
                {
                    this->m_logger << "file found\n";
                }
                else
                {
                    this->m_logger << "file NOT found\n";
                }
            }
        }
        this->m_logger << "----Getting file END----\n";

        return file;
    }
    template<class T>
    void c_file_bank<T>::erase_by_filepath(std::wstring_view filepath)
    {
        this->m_logger << "----Erasing object by filepath: " << filepath << "----\n";
        {
            if (this->m_vec_objects.empty())
            {
                this->m_logger << "ERROR: bank is empty\n";
            }
            else
            {
                auto iter = this->m_vec_objects.begin();

                uint64_t index = 0;

                bool found = false;

                for (uint64_t i = 0; i != this->m_vec_objects.size(); ++i, ++index)
                {
                    if (strings_are_equal(this->m_vec_objects[i]->filepath(), filepath))
                    {
                        found = true;
                        break;
                    }

                }
                if (found)
                {
                    this->m_logger << "object found\n";
                }
                else
                {
                    this->m_logger << "object NOT found\n";
                }

                iter += index;

                this->m_vec_objects.erase(iter);

                this->m_logger << "----Erasing object OK----\n";
            }
        }
        this->m_logger << "----Erasing object END----\n";
    }

}