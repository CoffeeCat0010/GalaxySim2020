#pragma once
#include <cstdint>
#include "../IO/GL_Logger.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Graphics
{
	class VertexArrayObj
	{
	private:
		uint32_t m_id;
		VertexBuffer* m_vertexBuffer;
		IndexBuffer* m_indexBuffer;

	public: 
		VertexArrayObj(VertexBuffer* vbuf, IndexBuffer* ibuf);
		VertexArrayObj() = default;
		~VertexArrayObj();

		/// <summary>
		/// Adds an attribute to the VAO. This will automatically bind and unbind the necessary buffers given on creation.
		/// </summary>
		/// <param name="index">This is the layout location of attributes in the GLSL shader</param>
		/// <param name="numPerAttrib">The number of values per attribute. For example, for position in 3d space you might have 3 values:
		/// x, y, and z coordiates. As per the opengl specification that this is built on, only 1,2,3,4 and GL_BGRA are accepted values</param>
		/// <param name="stride">The number of bytes that make up an entire vertex</param>
		/// <param name="offset">The offset in bytes of this attribute from the start of a vertex</param>
		void addAttrib(uint32_t index, uint32_t numPerAttrib, size_t stride, const void* offset, int type = GL_FLOAT);
		inline void bind() { GL_CHECK(glBindVertexArray(m_id)); };
		inline void unbind() { GL_CHECK(glBindVertexArray(0)); };
	};
}

