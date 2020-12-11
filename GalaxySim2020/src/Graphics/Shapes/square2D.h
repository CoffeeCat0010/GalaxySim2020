#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "renderable.h"
#include "../Primatives/vertex.h"
namespace Graphics
{

#define NUM_VERTS_IN_QUAD 4
#define NUM_INDICES_IN_QUAD 6

	class square2D : public renderable
	{
	private:
	//	unsigned int m_shaderProgramID;
		float m_scalar = 1;
		std::vector<Texture2D*> m_textures;
		std::vector<vertex> m_vArray =
		{
			{{-0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, 0},
			{{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, 0},
			{{ 0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, 0},
			{{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, 0}
		};

		uint32_t m_elements[6] = {
			0, 1, 2,
			2, 3, 0
		};

		glm::vec3 m_pos = { 0.0f, 0.0f ,0.0f };

	public:

		square2D(unsigned int shaderProgramID, float scalar, glm::vec3& pos, Texture2D* tex);
		square2D(unsigned int shaderProgramID, float scalar, float x, float y, float z, Texture2D* tex);

		~square2D() {};

		//Start inherited virtual functions
		std::pair<vertex*, size_t> getVertexData();
		std::pair<unsigned int*, size_t> getIndexData();
		void onUpdate();
		std::vector<Texture2D*> getTextures() { return m_textures; }

		inline void setScalar(float scalar) { m_scalar = scalar; }
		inline float getScalar() { return m_scalar; }

		inline glm::vec3& getPos() { return m_pos; };
		inline void setPos(float x, float y, float z) { m_pos = { x, y, z }; };
		inline void setPos(glm::vec3& pos) { m_pos = pos; };
	};
}