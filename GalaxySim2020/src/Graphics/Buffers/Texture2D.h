#pragma once
#include "Corepch.h"
#include <cstdint>


namespace Graphics
{
/// <summary>
/// This implements a basic Texture interface for opengl using the stb_image library.
/// It will handle many standard image file types including png and jpeg for a full list
/// please refer to their documentation here - https://github.com/nothings/stb
/// </summary>
	class Texture2D
	{
	private:
		uint32_t m_id;
		const std::string m_path;
		int m_width, m_height;
		int m_bitsPerPixel;
		unsigned char* m_buffer;
	public:
		Texture2D(const std::string& path);
		~Texture2D();

		uint32_t getID() { return m_id; }

		void bind(uint32_t slot = 0);
		void unbind();
	};
}
