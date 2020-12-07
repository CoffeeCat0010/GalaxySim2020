#pragma once
#include "GL/glew.h"
namespace Graphics
{
	class VertexBuffer
	{
	private:
		unsigned int m_id;
	public:
		VertexBuffer() { m_id = 0; }
		VertexBuffer(float* data, size_t size);
		~VertexBuffer();
		inline void bind() { glBindBuffer(GL_ARRAY_BUFFER, m_id); }
		inline void unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

		inline unsigned int getId() { return m_id; }
	};
}
