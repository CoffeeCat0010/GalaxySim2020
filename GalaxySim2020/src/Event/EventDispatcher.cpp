#include "Corepch.h"
#include "EventDispatcher.h"

namespace Application
{
	EventDispatcher* EventDispatcher::INSTANCE = nullptr; 
	EventDispatcher* EventDispatcher::getInstance ()
	{
		if (INSTANCE == nullptr )
			INSTANCE = new EventDispatcher();
		return INSTANCE;
	}
	void EventDispatcher::subscribe (std::weak_ptr<EventHandler> handler, Priority p)
	{
		if ( p == Priority::NORMAL )
			m_handlers.insert (m_handlers.end (), handler);
		else
			m_handlers.insert (m_handlers.begin (), handler);
	}
	void EventDispatcher::unsubscribe (std::weak_ptr<EventHandler> handler)
	{
		auto s_handler = std::make_shared<EventHandler> (handler);
		for ( auto it = m_handlers.begin (); it != m_handlers.end (); ++it )
		{
			if ( it->expired () )
				m_handlers.erase (it);
			if ( it->lock () == s_handler )
			{
				m_handlers.erase (it);
				break;
			}
		}
	}
	void EventDispatcher::upload (Event* e)
	{
		for ( auto it = m_handlers.begin (); it != m_handlers.end (); ++it )
		{
			if ( it->expired () )
				m_handlers.erase (it);
			it->lock ()->onEvent (e);
		}
	}
}