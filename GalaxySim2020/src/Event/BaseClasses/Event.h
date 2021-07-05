#pragma once
#include "Corepch.h"

namespace Application
{
	enum class EventType
	{
		None = 0, 
		// raw input
		MousePressed, MouseReleased, MouseScrolled, 
		ModifiedKeyPressed, KeyPressed, KeyReleased,
		// GUI input
		ButtonPressed, ButtonReleased,
		Hover, Drag, 
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
	/// Event base class. Currently all events are blocking and will be run immediately
	/// </summary>
	class Event
	{
	protected: 
		typedef uint64_t EventCat;
		EventType m_eventType;
		EventCat m_eventCategory;
		bool m_isHandled;
		Event (EventType eventType, EventCat eventCategory)
			: m_eventType (eventType), m_eventCategory (eventCategory)
		{}
	public:
		virtual EventType getEventType () const = 0;
		virtual std::string getName () const = 0;
		virtual EventCat getEventCategory () const { return m_eventCategory; }
		#ifdef DEBUG
		virtual std::string toString () const { return getName (); }
		#endif // DEBUG

		inline void handle () { m_isHandled = true; }
		inline bool isHandled () { return m_isHandled; }
	};
}