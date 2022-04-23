#pragma once
#include <string_view>
#include <vector>
#include <memory>
#include <array>

#include <owd_strings.h>
#include <owd_debug.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

namespace owd
{
    typedef uint64_t index_t;
	typedef uint8_t byte_t;
	typedef std::vector<byte_t> bytes_t;
	typedef std::shared_ptr<bytes_t> data_t;
    typedef std::array<float, 3> xyz_t; // array of space coordinates in Cartesian coordinate system

    /// <summary>
    /// array of orientaion coordinates in Cartesian coordinate system, 
    /// elements 0-2 are vector pointing where the object is "looking at"
    /// elements 3-5 are vector pointing whre the top of the object is pointing
    /// </summary>
    typedef std::array<float, 6> ori_t;

    constexpr float pi_ = 3.14159265358979324f;

	class c_basic_object
	{
    public:
        c_basic_object();

        virtual void reset();

        void set_name(std::wstring_view name);

        std::wstring_view name() const;

        virtual bool good() const;

        virtual bool set_bad();

        data_t& data();
        byte_t* data_raw_ptr();

        virtual size_t size_bytes() const;

    protected:
        c_logger m_logger;
        std::wstring m_name;

        data_t m_data_shared_ptr;


    private:
        bool m_good;
        bool default_good() const;
    };
    
    template<class T>
    class c_object_bank
    {
    public:
        c_object_bank();
        c_object_bank(std::wstring_view name);

        ~c_object_bank();

        void set_name(std::wstring_view name);

        void add(std::shared_ptr<T>& object);

        std::shared_ptr<T>& by_index(index_t i);
        std::shared_ptr<T>& by_name(std::wstring_view name);

        std::shared_ptr<T>& first();
        std::shared_ptr<T>& last();

        void clear();

        void erase(index_t index);
        void erase(std::wstring_view name);

        size_t count() const;

        bool empty() const;

        std::shared_ptr<T>& operator[](index_t i);
        std::shared_ptr<T>& operator[](std::wstring_view name);

    protected:
        c_logger m_logger;
        static std::shared_ptr<T> m_empty_object;

        std::wstring m_name;
        std::vector<std::shared_ptr<T>> m_vec_objects;

        bool check_double(std::shared_ptr<T>& object);
    };

    template<class T>
    std::shared_ptr<T> c_object_bank<T>::m_empty_object{};

    template<class T>
    c_object_bank<T>::c_object_bank()
        :
        m_name(L"object_bank"),
        m_vec_objects(),
        m_logger(L"object_bank_logger")
    {
    }

    template<class T>
    c_object_bank<T>::c_object_bank(std::wstring_view name)
        :
        m_name(name),
        m_vec_objects(),
        m_logger(L"object_bank_logger")
    {
    }

    template<class T>
    c_object_bank<T>::~c_object_bank()
    {
    }

    template<class T>
    void c_object_bank<T>::set_name(std::wstring_view name)
    {
        this->m_name = name;
    }

    template<class T>
    void c_object_bank<T>::add(std::shared_ptr<T>& object)
    {
        if (object->good())
        {
            if (this->check_double(object))
            {
                this->m_vec_objects.push_back(object);
            }
            else
            {
            }
        }
        else
        {
        }
    }
    template<class T>
    std::shared_ptr<T>& c_object_bank<T>::by_index(index_t i)
    {
        if (this->m_vec_objects.empty())
        {
        }
        else
        {
            if (i < this->m_vec_objects.size())
            {
                return this->m_vec_objects[i];
            }
            else
            {
            }
        }

        return m_empty_object;
    }
    template<class T>
    std::shared_ptr<T>& c_object_bank<T>::by_name(std::wstring_view name)
    {
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

    template<class T>
    std::shared_ptr<T>& c_object_bank<T>::first()
    {
        if (this->m_vec_objects.empty())
        {
            return m_empty_object;
        }
        else
        {
            return this->m_vec_objects.front();
        }
    }

    template<class T>
    std::shared_ptr<T>& c_object_bank<T>::last()
    {
        if (this->m_vec_objects.empty())
        {
            return m_empty_object;
        }
        else
        {
            return this->m_vec_objects.back();
        }
    }

    template<class T>
    void c_object_bank<T>::clear()
    {
        this->m_vec_objects.clear();
    }
    template<class T>
    void c_object_bank<T>::erase(uint64_t index)
    {
        {
            if (this->m_vec_objects.empty())
            {
            }
            else
            {
                if (index < this->m_vec_objects.size())
                {
                    auto iter = this->m_vec_objects.begin();

                    iter += index;

                    this->m_vec_objects.erase(iter);

                }
                else
                {
                }
            }
        }
    }
    template<class T>
    void c_object_bank<T>::erase(std::wstring_view name)
    {
        if (this->m_vec_objects.empty())
        {
        }
        else
        {
            auto iter = this->m_vec_objects.begin();

            for (uint64_t i = 0; i != this->m_vec_objects.size(); ++i)
            {
                if (owd::strings_are_equal(this->m_vec_objects[i]->name(), name))
                {
                    iter += i;
                    this->m_vec_objects.erase(iter);
                }
            }
        }
    }

    template<class T>
    size_t c_object_bank<T>::count() const
    {
        return this->m_vec_objects.size();
    }

    template<class T>
    bool c_object_bank<T>::empty() const
    {
        return this->m_vec_objects.empty();
    }

    template<class T>
    std::shared_ptr<T>& c_object_bank<T>::operator[](index_t i)
    {
        return this->by_index(i);
    }
    template<class T>
    std::shared_ptr<T>& owd::c_object_bank<T>::operator[](std::wstring_view name)
    {
        return this->by_name(name);
    }
    template<class T>
    bool c_object_bank<T>::check_double(std::shared_ptr<T>& object)
    {
        bool found_double = false;
        for (uint64_t i = 0; i != this->m_vec_objects.size(); ++i)
        {
            if (owd::strings_are_equal(this->m_vec_objects[i]->name(), object->name()))
            {
                found_double = true;
                break;
            }
        }
        return found_double;
    }

}