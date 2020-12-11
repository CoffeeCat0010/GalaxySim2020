#include "square2D.h"


namespace Graphics
{
	square2D::square2D(unsigned int shaderProgramID, float scalar, glm::vec3& pos, Texture2D* tex)
		:renderable(shaderProgramID), m_scalar(scalar), m_pos(pos), m_textures(std::vector<Texture2D*>())
	{
		m_textures.push_back(tex);
		for (vertex v : m_vArray)
		{
			v.m_textureID = tex->getID();
		}
	}

	square2D::square2D(unsigned int shaderProgramID, float scalar, float x, float y, float z, Texture2D* tex)
		: renderable(shaderProgramID), m_scalar(scalar), m_pos({ x, y, z }), m_textures(std::vector<Texture2D*>())
	{
		m_textures.push_back(tex);
		for (vertex& v : m_vArray)
		{
			v.m_textureID = tex->getID();
		}
	}

	std::pair<vertex*, size_t> square2D::getVertexData()
	{
		return {m_vArray.data(), NUM_VERTS_IN_QUAD};
	}

	std::pair<unsigned int*, size_t> square2D::getIndexData()
	{
		return {m_elements, NUM_INDICES_IN_QUAD};
	}

	void square2D::onUpdate()
	{}
}