#pragma once
#include <string_view>
#include <vector>
#include <memory>
#include <owd_strings.h>

namespace owd
{
    typedef uint64_t index_t;
	typedef uint8_t byte_t;
	typedef std::vector<byte_t> bytes_t;
	typedef std::shared_ptr<bytes_t> data_t;

	class c_basic_object
	{
	public:
		c_basic_object(std::wstring_view name);
		c_basic_object();

		virtual void reset();

		inline void set_name(std::wstring_view name) { m_name = name; }

		inline std::wstring_view name() const { return m_name; }

		virtual bool good() const;

		inline data_t& data() { return m_data_shared_ptr; }
		inline byte_t* data_raw_ptr() { return data()->data(); }

		virtual inline size_t size_bytes() const { return m_data_shared_ptr->size(); }
	protected:
        std::wstring m_name{ L"basic_object" };

		data_t m_data_shared_ptr = std::make_shared<bytes_t>();

		inline bool default_good() const { return m_good; }

	private:
		bool m_good = true;
	};

    
    template <class T>
    class c_object_bank
    {
    public:
        c_object_bank();
        c_object_bank(std::wstring_view name);

        ~c_object_bank();

        inline void set_name(std::wstring_view name) { this->m_name = name; }

        inline std::wstring_view name() { return this->m_name; }

        void add(std::shared_ptr<T>& object);

        std::shared_ptr<T>& by_index(uint64_t i);
        std::shared_ptr<T>& by_name(std::wstring_view name);

        std::shared_ptr<T>& first();
        std::shared_ptr<T>& last();

        void clear();

        void erase(uint64_t index);
        void erase(std::wstring_view name);

        virtual inline size_t size_bytes() const { return this->m_vec_objects.size(); }

        inline size_t count() { return this->m_vec_objects.size(); }

        inline bool empty() { return (this->count() > 0); }

        inline std::shared_ptr<T>& operator[](index_t i) { return this->by_index(i); }
        inline std::shared_ptr<T>& operator[](std::wstring_view name) { return this->by_name(name); }

    protected:
        static std::shared_ptr<T> m_empty_object;

        std::wstring m_name{ L"object_bank_object" };

        std::vector<std::shared_ptr<T>> m_vec_objects{};

        bool check_double(const T& object);
        bool check_double(std::shared_ptr<T>& object);
    };

    template <class T>
    std::shared_ptr<T> c_object_bank<T>::m_empty_object{};

    template<class T>
    c_object_bank<T>::c_object_bank()
    {
    }

    template<class T>
    c_object_bank<T>::c_object_bank(std::wstring_view name)
        :
        m_name(name)
    {
    }

    template<class T>
    c_object_bank<T>::~c_object_bank()
    {
    }

    template<class T>
    void c_object_bank<T>::add(std::shared_ptr<T>& object)
    {
        {
            if (object->good())
            {
                if (this->check_double(*object))
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
    }
    template<class T>
    std::shared_ptr<T>& c_object_bank<T>::by_index(uint64_t i)
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
        if (m_vec_objects.empty())
        {
            return m_empty_object;
        }
        else
        {
            return m_vec_objects.front();
        }
    }

    template<class T>
    std::shared_ptr<T>& c_object_bank<T>::last()
    {
        if (m_vec_objects.empty())
        {
            return m_empty_object;
        }
        else
        {
            return m_vec_objects.back();
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
    bool c_object_bank<T>::check_double(const T& object)
    {
        bool found_double = false;
        for (uint64_t i = 0; i != this->m_vec_objects.size(); ++i)
        {
            if (owd::strings_are_equal(this->m_vec_objects[i]->name(), object.name()))
            {
                found_double = true;
                break;
            }
        }
        return found_double;
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