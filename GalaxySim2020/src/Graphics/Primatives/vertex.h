#pragma once
#include <glm/glm.hpp>

namespace Graphics
{
	struct vertex
	{
		glm::vec3 m_pos;
		glm::vec4 m_color;
		glm::vec2 m_texCoords;
		float m_textureID;
	};
}