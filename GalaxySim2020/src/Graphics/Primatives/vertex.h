#pragma once
#include "Corepch.h"

namespace Graphics
{
	struct vertex
	{
		glm::vec3 m_pos;
		glm::vec4 m_color;
		glm::vec2 m_texCoords;
		int m_textureID;
	};
}