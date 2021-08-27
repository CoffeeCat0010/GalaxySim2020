#pragma once
#include "Corepch.h"
#include "Utility/Math/MVec.h"

namespace Graphics
{
	class IOpenglContext
	{
	protected:
		Util::Vec2i m_contextDim;
	public:
		IOpenglContext(int32_t sizeX, int32_t sizeY)
			:m_contextDim ({sizeX, sizeY})
		{}
		/// <summary>
		/// Initialize the opengl library
		/// </summary>
		/// <returns> True if initialization is sucessful. </returns>
		virtual bool init () = 0;
		/// <summary>
		/// makes the opengl context current in this thread 
		/// </summary>
		virtual void makeOGLContextCurrent () = 0;
		/// <summary>
		/// swaps the buffers to display the scene
		/// </summary>
		virtual void paint () = 0;
		virtual float getAspectRatio () { return (float)(m_contextDim.x / m_contextDim.y); }
	};
}