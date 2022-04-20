#pragma once
#include <owd_debug.h>
#include <owd_filesystem.h>

#include "opengl/opengl.h"
#include "stb_image/stb_image.h"



namespace owd_lib
{
	class c_texture : public owd::c_file
	{
	public:

		static int32_t init_stbi();

		c_texture();
		c_texture(std::wstring_view filepath);
		c_texture(std::wstring_view filepath, std::wstring_view name);
		~c_texture();

		void init();
		void terminate();

		inline int32_t w() const
		{
			return m_w;
		}

		inline int32_t h() const
		{
			return m_h;
		}

		inline int32_t depth_bits() const // bits per pixel (all channels counted)
		{
			return m_depth_bits;
		}

		inline int32_t depth_bytes() const // bits per pixel (all channels counted)
		{
			return m_depth_bytes;
		}

		bool load(std::wstring_view filepath) override;
		bool load(std::wstring_view filepath, std::wstring_view name) override;
		
		inline void bind()
		{
			GL_CALL(glBindTexture(GL_TEXTURE_2D, m_ogl_id));
		}
		inline void unbind()
		{
			GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
		}
		inline GLuint gl_id() const { return m_ogl_id; }

	private:
		uint32_t m_ogl_id{};

		int32_t m_w = -1;
		int32_t m_h = -1;

		int32_t m_channels_count = -1;

		int32_t m_depth_bits  = 32; // bits per pixel (all channels counted)
		int32_t m_depth_bytes = 4; // bytes per pixel (all channels counted)

		owd::byte_t* m_data_buffer = nullptr;
	};
	typedef std::shared_ptr<c_texture> texture_t;
}