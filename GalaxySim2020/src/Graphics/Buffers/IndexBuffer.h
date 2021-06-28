#pragma once
#include "Corepch.h"
#include "GL/glew.h"
namespace Graphics {
	class IndexBuffer
	{
	private:
		unsigned int m_id;
	public:
		IndexBuffer() { m_id = 0; }
		IndexBuffer(const unsigned int* data, size_t size);
		~IndexBuffer();
		void bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); }
		inline void unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

		inline unsigned int getId() const{ return m_id; }
	};
}

