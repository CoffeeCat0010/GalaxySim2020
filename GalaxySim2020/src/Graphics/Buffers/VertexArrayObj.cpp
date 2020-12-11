#include "GL/glew.h"
#include "VertexArrayObj.h"
#include "../IO/GL_Logger.h"
namespace Graphics
{
	VertexArrayObj::VertexArrayObj(VertexBuffer* vbuf, IndexBuffer* ibuf)
		:m_vertexBuffer(vbuf), m_indexBuffer(ibuf)
	{
		GL_CHECK(glGenVertexArrays(1, &m_id));
	}

	VertexArrayObj::~VertexArrayObj()
	{
		GL_CHECK(glDeleteVertexArrays(1, &m_id));
	}

	void VertexArrayObj::addAttrib(uint32_t index, uint32_t numPerAttrib, size_t stride, const void* offset, int type)
	{
		bind();
		m_vertexBuffer->bind();
		m_indexBuffer->bind();
		GL_CHECK(glEnableVertexAttribArray(index));
		GL_CHECK(glVertexAttribPointer(index, numPerAttrib, GL_FLOAT, false, stride, offset));
		m_vertexBuffer->unbind();
		m_indexBuffer->unbind();
		unbind();
	}
}