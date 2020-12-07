#include "square2D.h"


namespace Graphics
{
	square2D::square2D(unsigned int shaderProgramID, float scalar, glm::vec3& pos)
		:renderable(shaderProgramID), m_scalar(scalar), m_pos(pos)
	{}

	square2D::square2D(unsigned int shaderProgramID, float scalar, float x, float y, float z)
		: renderable(shaderProgramID), m_scalar(scalar), m_pos({ x, y, z })
	{}

	std::pair<vertex*, size_t> square2D::getVertexData()
	{
		return {m_vArray, NUM_VERTS_IN_QUAD};
	}

	std::pair<unsigned int*, size_t> square2D::getIndexData()
	{
		return {m_elements, NUM_INEDECIES_IN_QUAD};
	}

	void square2D::onUpdate()
	{}
}