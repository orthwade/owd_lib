#include "c_convert_strings.h"

namespace owd_lib
{
    c_convert_strings* c_convert_strings::m_singleton = nullptr;

    c_convert_strings::c_convert_strings()
    {
        
    }

   c_convert_strings::~c_convert_strings()
    {
       delete m_singleton;
       m_singleton = nullptr;
    }

   //void c_convert_strings::utf_8_to_unicode(const std::string& utf_8_in, std::wstring& unicode_out)
   //{
   //    if (m_singleton == nullptr)
   //    {
   //        m_singleton = new c_convert_strings();
   //    }
   //    unicode_out = unicode(utf_8_in);
   //}

   //void c_convert_strings::unicode_to_utf_8(const std::wstring& unicode_in, std::string& utf_8_out)
   //{
   //    if (m_singleton == nullptr)
   //    {
   //        m_singleton = new c_convert_strings();
   //    }
   //    utf_8_out = utf_8(unicode_in);
   //}

   //std::wstring c_convert_strings::unicode(const std::string& utf_8_in)
   //{
   //    if (m_singleton == nullptr)
   //    {
   //        m_singleton = new c_convert_strings();
   //    }
   //    return m_singleton->static_converter.from_bytes(utf_8_in);
   //}

   //std::string c_convert_strings::utf_8(const std::wstring& unicode_in)
   //{
   //    if (m_singleton == nullptr)
   //    {
   //        m_singleton = new c_convert_strings();
   //    }
   //    return m_singleton->static_converter.to_bytes(unicode_in);
   //}
   std::wstring c_convert_strings::unicode(const char* utf_8_in)
   {
       if (m_singleton == nullptr)
       {
           m_singleton = new c_convert_strings();
       }
       return m_singleton->m_converter.from_bytes(utf_8_in);
   }
   std::string c_convert_strings::utf_8(const wchar_t* unicode_in)
   {
       if (m_singleton == nullptr)
       {
           m_singleton = new c_convert_strings();
       }
       return m_singleton->m_converter.to_bytes(unicode_in);
   }
   std::wstring c_convert_strings::unicode(const std::string_view utf_8_in)
   {
       return unicode(utf_8_in.data());
   }
   std::string c_convert_strings::utf_8(const std::wstring_view unicode_in)
   {
       return utf_8(unicode_in.data());
   }
}

