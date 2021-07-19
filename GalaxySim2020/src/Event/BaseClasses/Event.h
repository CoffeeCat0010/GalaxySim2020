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

		//App events
		close, configurationUpdated,
	};

	enum EventCategory
	{
		None = 0,
	  CatInputEvent = BIT(0),
		CatKeyEvent = BIT(1),
		CatMouseEvent = BIT(2),
		CatGUIEvent = BIT(3),
		CatAppEvent = BIT(4)

	};

	/// <summary>
	/// Event base class. Currently all events are blocking and will be run immediately
	/// </summary>
	class Event
	{
	private:
		bool m_isHandled;
	protected: 
		typedef uint64_t EventCat;
		std::mutex m_mutex;
		EventType m_eventType;
		EventCat m_eventCategory;
		Event (EventType eventType, EventCat eventCategory)
			: m_eventType (eventType), m_eventCategory (eventCategory), m_isHandled(false)
		{}
	public:
		virtual EventType getEventType () const = 0;
		virtual std::string getName () const = 0;
		virtual EventCat getEventCategory () const { return m_eventCategory; }
		#ifdef DEBUG
		virtual std::string toString () const { return getName (); }
		#endif // DEBUG

		inline void handle () {
			m_mutex.lock();
			m_isHandled = true;
			m_mutex.unlock();
		}
		inline bool isHandled () { 
			m_mutex.lock();
			bool result = m_isHandled;
			m_mutex.unlock();
			return result;
			}
	};
}