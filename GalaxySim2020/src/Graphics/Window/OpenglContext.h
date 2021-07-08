#pragma once
#include "Corepch.h"
#include "Math/MVec.h"

namespace Graphics
{
	class IOpenglContext
	{
	protected:
		Application::Vec2i m_contextDim;
	public:
		IOpenglContext(int32_t sizeX, int32_t sizeY)
			:m_contextDim ({sizeX, sizeY})
		{}
		/// <summary>
		/// makes the opengl context current in this thread 
		/// </summary>
		virtual void makeOGLContextCurrent () = 0;
		/// <summary>
		/// swaps the buffers to display the scene
		/// </summary>
		virtual void swapBuffers () = 0;
		virtual float getAspectRatio () { return (float)(m_contextDim.x / m_contextDim.y); }
	};
}