#pragma once
#include "Corepch.h"

namespace Application
{
	enum class EventType
	{
		None = 0, 
		// raw input
		MousePressedEvent, MouseReleasedEvent, MouseLocationEvent,
		KeyPressedEvent, KeyReleasedEvent,
		// GUI input
		ButtonPressedEvent, ButtonReleasedEvent,

		HoverEvent, DragEvent, 
	};

	enum EventCategory
	{
		None = 0,
	  CatInputEvent = 1 << 0,
		CatKeyEvent = 1 << 1,
		CatMouseEvent = 1 << 2,
		CatGUIEvent = 1 << 3
	};

	/// <summary>
	/// Event template class. Currently all events are blocking and will be run imediately
	/// </summary>
	class Event
	{
	private:
		typedef uint64_t EventCat;
		EventType m_eventType;
		EventCat m_eventCategory;
	protected: 
		Event (EventType eventType, EventCat eventCategory)
			: m_eventType (eventType), m_eventCategory (eventCategory)
		{}
	public:
		virtual EventType getEventType () = 0;
		virtual std::string getName () = 0;
		virtual EventCat getEventCategory () { return m_eventCategory; };
		
	};
	class MouseEvent: public Event
	{
	protected:
		MouseEvent (EventType eventType)
			:Event(eventType, CatInputEvent | CatMouseEvent)
		{}
	public:
		virtual EventType getEventType () override = 0;
		virtual std::string getName () override = 0;

	};


}