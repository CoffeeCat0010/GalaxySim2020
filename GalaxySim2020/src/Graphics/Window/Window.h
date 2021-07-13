#pragma once
#include "Corepch.h"
#include "Event/BaseClasses/EventDispatcher.h"
#include "Math/MVec.h"
namespace Graphics
{
	class IWindow
	{
	protected:
		Application::Vec2i m_windowDim;
		std::shared_ptr<Application::EventDispatcher> m_eventDis;
	public: 
		IWindow(int32_t sizeX, int32_t sizeY, std::shared_ptr<Application::EventDispatcher> dispatcher)
			: m_windowDim ({sizeX, sizeY}), m_eventDis(dispatcher)
		{}
		virtual bool init () { return true; }
		virtual Application::Vec2i& getWindowDimensions () { return m_windowDim; }
		/// <summary>
		/// This polls the events from the windowing system and sends them to the dispatcher
		/// </summary>
		virtual void pollEvents () = 0;
	};
}