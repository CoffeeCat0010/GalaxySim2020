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
	};
}