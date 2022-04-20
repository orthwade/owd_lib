#include "c_vertex_buffer_element.h"

namespace owd_lib
{
    c_vertex_buffer_element::c_vertex_buffer_element()
    {
    }

    c_vertex_buffer_element::c_vertex_buffer_element(uint32_t type, uint32_t count, bool normalized)
        :
        m_count     (count     ),
        m_type      (type      ),
        m_normalized(normalized)
    {
    }

   c_vertex_buffer_element::~c_vertex_buffer_element()
    {
    }

    c_vertex_buffer_element::c_vertex_buffer_element(const c_vertex_buffer_element& other)
    {
        *this = other;
    }

    c_vertex_buffer_element& owd_lib::c_vertex_buffer_element::operator=(const c_vertex_buffer_element& other)
    {
        if (this != &other)
        {
            m_count         = other.m_count;
            m_type          = other.m_type;
            m_normalized    = other.m_normalized;
        }
        return *this;
    }

    std::wstring_view c_vertex_buffer_element::ogl_type_str()
    {
        std::wstring ogl_type_str{};

        switch (m_type)
        {
            case    GL_BYTE             : ogl_type_str = L"GL_BYTE          ";   break;   
            case    GL_UNSIGNED_BYTE    : ogl_type_str = L"GL_UNSIGNED_BYTE ";   break;   
            case    GL_SHORT            : ogl_type_str = L"GL_SHORT         ";   break;   
            case    GL_UNSIGNED_SHORT   : ogl_type_str = L"GL_UNSIGNED_SHORT";   break;    
            case    GL_INT              : ogl_type_str = L"GL_INT           ";   break;   
            case    GL_UNSIGNED_INT     : ogl_type_str = L"GL_UNSIGNED_INT  ";   break;   
            case    GL_FLOAT            : ogl_type_str = L"GL_FLOAT         ";   break;   
            case    GL_2_BYTES          : ogl_type_str = L"GL_2_BYTES       ";   break;   
            case    GL_3_BYTES          : ogl_type_str = L"GL_3_BYTES       ";   break;   
            case    GL_4_BYTES          : ogl_type_str = L"GL_4_BYTES       ";   break;   
            case    GL_DOUBLE           : ogl_type_str = L"GL_DOUBLE        ";   break;   
        default:
            ogl_type_str = L"UNKNOWN_TYPE";
            break;
        }
        return ogl_type_str;
    }

    std::wstring_view c_vertex_buffer_element::ogl_type_str(uint32_t type)
    {
        std::wstring ogl_type_str{};

        switch (type)
        {
            case    GL_BYTE             : ogl_type_str = L"GL_BYTE          ";   break;   
            case    GL_UNSIGNED_BYTE    : ogl_type_str = L"GL_UNSIGNED_BYTE ";   break;   
            case    GL_SHORT            : ogl_type_str = L"GL_SHORT         ";   break;   
            case    GL_UNSIGNED_SHORT   : ogl_type_str = L"GL_UNSIGNED_SHORT";   break;    
            case    GL_INT              : ogl_type_str = L"GL_INT           ";   break;   
            case    GL_UNSIGNED_INT     : ogl_type_str = L"GL_UNSIGNED_INT  ";   break;   
            case    GL_FLOAT            : ogl_type_str = L"GL_FLOAT         ";   break;   
            case    GL_2_BYTES          : ogl_type_str = L"GL_2_BYTES       ";   break;   
            case    GL_3_BYTES          : ogl_type_str = L"GL_3_BYTES       ";   break;   
            case    GL_4_BYTES          : ogl_type_str = L"GL_4_BYTES       ";   break;   
            case    GL_DOUBLE           : ogl_type_str = L"GL_DOUBLE        ";   break;   
        default:
            ogl_type_str = L"UNKNOWN_TYPE";
            break;
        }
        return ogl_type_str;
    }

    uint32_t c_vertex_buffer_element::ogl_type_size_bytes()
    {
        uint32_t ogl_type_size{};

        switch (m_type)
        {
            case    GL_BYTE             : ogl_type_size = 1;   break;   
            case    GL_UNSIGNED_BYTE    : ogl_type_size = 1;   break;   
            case    GL_SHORT            : ogl_type_size = 2;   break;   
            case    GL_UNSIGNED_SHORT   : ogl_type_size = 2;   break;    
            case    GL_INT              : ogl_type_size = 4;   break;   
            case    GL_UNSIGNED_INT     : ogl_type_size = 4;   break;   
            case    GL_FLOAT            : ogl_type_size = 4;   break;   
            case    GL_2_BYTES          : ogl_type_size = 2;   break;   
            case    GL_3_BYTES          : ogl_type_size = 3;   break;   
            case    GL_4_BYTES          : ogl_type_size = 4;   break;   
            case    GL_DOUBLE           : ogl_type_size = 8;   break;   
        default:
            ogl_type_size = 0;
            break;
        }
        return ogl_type_size;
    }

    uint32_t c_vertex_buffer_element::ogl_type_size_bytes(uint32_t type)
    {
        uint32_t ogl_type_size{};

        switch (type)
        {
            case    GL_BYTE             : ogl_type_size = 1;   break;   
            case    GL_UNSIGNED_BYTE    : ogl_type_size = 1;   break;   
            case    GL_SHORT            : ogl_type_size = 2;   break;   
            case    GL_UNSIGNED_SHORT   : ogl_type_size = 2;   break;    
            case    GL_INT              : ogl_type_size = 4;   break;   
            case    GL_UNSIGNED_INT     : ogl_type_size = 4;   break;   
            case    GL_FLOAT            : ogl_type_size = 4;   break;   
            case    GL_2_BYTES          : ogl_type_size = 2;   break;   
            case    GL_3_BYTES          : ogl_type_size = 3;   break;   
            case    GL_4_BYTES          : ogl_type_size = 4;   break;   
            case    GL_DOUBLE           : ogl_type_size = 8;   break;   
        default:
            ogl_type_size = 0;
            break;
        }
        return ogl_type_size;
    }

}

