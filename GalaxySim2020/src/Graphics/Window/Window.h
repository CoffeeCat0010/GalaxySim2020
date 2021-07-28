#pragma once
#include "Corepch.h"
#include "Event/EventDispatcher.h"
#include "Math/MVec.h"
namespace Graphics
{
	class IWindow
	{
	protected:
		Application::Vec2i m_windowDim;
		bool running;
	public: 
		IWindow(int32_t sizeX, int32_t sizeY)
			: m_windowDim ({sizeX, sizeY}), running(false)
		{}
		virtual bool shouldClose() {return running;}
		virtual bool init () { return true; }
		virtual Application::Vec2i& getWindowDimensions () { return m_windowDim; }
		/// <summary>
		/// This polls the events from the windowing system and sends them to the dispatcher
		/// </summary>
		virtual void pollEvents () = 0;
		virtual void close () = 0;
	};
}