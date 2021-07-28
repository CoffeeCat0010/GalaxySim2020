#include "Corepch.h"
#include "EventDispatcher.h"

namespace Application
{
	void EventDispatcher::subscribe (std::weak_ptr<std::function<void(Event* e)>> callback, Priority p)
	{
		if ( p == Priority::NORMAL )
			m_callbacks.insert (m_callbacks.end (), callback);
		else
			m_callbacks.insert (m_callbacks.begin (), callback );
	}
	void EventDispatcher::unsubscribe (std::weak_ptr<std::function<void (Event* e)>> callback)
	{
		auto s_callback = callback.lock();
		for ( auto it = m_callbacks.begin (); it != m_callbacks.end (); ++it )
		{
			if ( it->expired () )
				m_callbacks.erase (it);
			if ( it->lock () == s_callback )
			{
				m_callbacks.erase (it);
				break;
			}
		}
	}
	void EventDispatcher::dispatch (Event* e)
	{
		for ( auto it = m_callbacks.begin (); it != m_callbacks.end (); ++it )
		{
			if ( it->expired () )
				m_callbacks.erase (it);
			(*it->lock ()->target<void(*)(Event*)>())(e);
		}
	}
}