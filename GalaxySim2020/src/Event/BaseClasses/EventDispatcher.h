#pragma once
#include "Corepch.h"
#include "Event.h"
#include "EventHandlers.h"

namespace Application
{

	class EventDispatcher
	{
	private:
		std::vector<EventHandler*> m_handlers;
	public:
		static const enum class Priority{ CRITICAL, NORMAL };
		EventDispatcher ()
		{}
		/// <summary>
		/// 
		/// </summary>
		void subscribe (EventHandler* handler, Priority p = Priority::NORMAL)
		{
			if ( p == Priority::NORMAL )
				m_handlers.insert(m_handlers.end (), handler);
			else
				m_handlers.insert (m_handlers.begin (), handler);
		}
		void unsubscribe (EventHandler* handler)
		{
			for ( auto it = m_handlers.begin (); it != m_handlers.end (); ++it )
			{
				if ( *it == handler )
				{
					m_handlers.erase (it);
					break;
				}
			}
		}
		void dispatch (Event& e)
		{
			for ( auto it = m_handlers.begin (); it != m_handlers.end (); ++it )
			{
				(*it)->onEvent (e);
			}
		}
	};
}