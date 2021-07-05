#include "Corepch.h"
#include "Star.h"
namespace Graphics
{
	Star::Star (uint32_t shaderID, glm::vec3 pos, float scalar)
		:renderable (shaderID), m_emptyTextures (std::vector<Texture2D*> ()), m_pos (pos), m_scalar (scalar),
		m_translationMat (glm::translate (pos)), m_rotationMat (glm::mat4(1.0f)),
		m_scalarMat (glm::scale (glm::vec3 (scalar, scalar, scalar)))
	{}
	void Star::setPos (glm::vec3& newPos)
	{
		m_pos = newPos;
		m_translationMat = glm::translate (m_pos);
	}
	void Star::setScalar (float scalar)
	{
		m_scalar = scalar;
		m_scalarMat = glm::scale (glm::vec3 (scalar, scalar, scalar));
	}

	std::pair<vertex*, size_t> Star::getVertexData ()
	{
		return {m_verts.data(), m_verts.size()};
	}
	std::pair<uint32_t*, size_t> Star::getIndexData ()
	{
		return {m_indecies.data(), m_indecies.size()};
	}
	std::vector<Texture2D*> Star::getTextures ()
	{
		return m_emptyTextures;
		
	}
	glm::mat4 Star::getModelMatrix ()
	{
		return m_translationMat * m_rotationMat * m_scalarMat;
	}
	void Star::onUpdate ()
	{
		
	}
}