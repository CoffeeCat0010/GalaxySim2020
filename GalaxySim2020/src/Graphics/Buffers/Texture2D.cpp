#include "Texture2D.h"
#include "IO/GL_Logger.h"
#include "stb_image/stb_image.h"
Graphics::Texture2D::Texture2D(const std::string& path)
	:m_id(0), m_path(path),  m_width(0), m_height(0), m_bitsPerPixel(0), m_buffer(nullptr)
{
	stbi_set_flip_vertically_on_load(1);
	m_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bitsPerPixel, 4);

	GL_CHECK(glGenTextures(1, &m_id));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_id));

	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

	stbi_image_free(m_buffer);
}

Graphics::Texture2D::~Texture2D()
{
	GL_CHECK(glDeleteTextures(1, &m_id));
}

/// <summary>
/// This function binds a texture to a texture image unit: GL_TEXTURE0 by default. For the sake of simplicity, it does not
/// check the number of available texture image units. It is the responsibity of the calling function
/// to ensure that the slot does not exceed GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1; See https://docs.gl/gl4/glActiveTexture
/// for information.
/// </summary>
/// <param name="slot">The slot that you would like to bind to. It is set to 0 (the first slot) if none is given. </param>
void Graphics::Texture2D::bind(uint32_t slot)
{
	GL_CHECK(glActiveTexture(GL_TEXTURE0 + slot));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_id));
}

void Graphics::Texture2D::unbind()
{
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}
