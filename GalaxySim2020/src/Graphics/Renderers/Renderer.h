#pragma once
#include "Corepch.h"
#include "Graphics/Shapes/renderable.h"
namespace Graphics{
	class IRenderer
	{
		//s_maxTextureUnits should be thought of as effectively const
		static int s_maxTextureUnits = -1;
	public:
		static int getMaxTextureUnits ()
		{
			if ( s_maxTextureUnits == -1 )
			{
				GL_CHECK (glGetIntegerv (GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &s_maxTextureUnits));
			}
			return s_maxTextureUnits;
		}
		virtual void addMesh (renderable& mesh) = 0;
		virtual void render () = 0;
	};
}