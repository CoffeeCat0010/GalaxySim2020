#include "VertexBuffer.h"

namespace Graphics
{
	VertexBuffer::VertexBuffer(float* data, size_t size)
	{
		glGenBuffers(1, &m_id);
		bind();
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}
}