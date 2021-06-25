#pragma once
#include "renderable.h"
#include <vector>
#include "glm/glm.hpp"
namespace Graphics
{
	class Star : public renderable
	{
	private:
		std::vector<Texture2D*> m_emptyTextures;
		std::vector<vertex> m_verts = 
		{
			{{ 0.2f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, 0},
			{{ 0.0f, 0.5f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, 0},
			{{-0.2f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, 0},
		};

		std::vector<uint32_t> m_indecies = { 0, 1, 2 };
		glm::vec3 m_pos = { 0.0f, 0.0f, 0.0f };
		float m_scalar;
		glm::mat4 m_translationMat;
		glm::mat4 m_rotationMat;
		glm::mat4 m_scalarMat;

	public:
		Star () :renderable(0), m_scalar (1.0f), m_translationMat (glm::mat4 ()), m_rotationMat (glm::mat4 ()), m_scalarMat (glm::mat4 ()) {};
		Star (uint32_t shaderID, glm::vec3 pos, float scalar = 1.0f);
		void setPos (glm::vec3& newPos);
		void setScalar (float scalar);


		// Inherited via renderable
		virtual std::pair<vertex*, size_t> getVertexData () override;
		virtual std::pair<uint32_t*, size_t> getIndexData () override;
		virtual std::vector<Texture2D*> getTextures () override;

		virtual glm::mat4 getModelMatrix () override;
		virtual void onUpdate () override;
	};
}

