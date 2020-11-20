#include "IndexBuffer.h"
namespace Graphics {
	IndexBuffer::IndexBuffer(const unsigned int* data, size_t size)
	{
		glGenBuffers(1, &m_id);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}
}
