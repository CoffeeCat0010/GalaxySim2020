#pragma once

#include "Corepch.h"
#include "Event/BaseClasses/Event.h"
namespace Application
{
	class ApplicationEvent : public Event
	{
	public:
		ApplicationEvent (EventType type)
			:Event (type, EventCategory::CatAppEvent)
		{}
	};
	class AppCloseEvent : public ApplicationEvent
	{
	public:
		AppCloseEvent ()
			:ApplicationEvent(EventType::close)
		{}
		inline EventType getEventType () const override { return m_eventType; }
		inline std::string getName () const override { return "AppCloseEvent"; }
	};
}