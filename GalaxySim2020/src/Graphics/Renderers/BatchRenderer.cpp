#include "BatchRenderer.h"


namespace Graphics
{
	BatchRenderer::BatchRenderer()
		:m_maxVerts(DEFAULT_MAX_VERTS)
	{
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &c_maxTextureUnits);
	}
	
	BatchRenderer::BatchRenderer(uint32_t maxVerts)
		: m_maxVerts(maxVerts)
	{}
}
