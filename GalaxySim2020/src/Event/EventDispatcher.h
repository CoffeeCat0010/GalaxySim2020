#pragma once
#include "Corepch.h"
#include "BaseClasses/Event.h"
#include "BaseClasses/EventHandlers.h"
#include "BaseClasses/EventBroadcaster.h"

namespace Application
{

	class EventDispatcher
	{
	private:
		typedef std::shared_ptr<Event> sharedEvtPtr;
		static EventDispatcher* INSTANCE;
		std::vector<std::weak_ptr<std::function<void(sharedEvtPtr e)>>> m_callbacks;
	public:
		static const enum class Priority { CRITICAL, NORMAL };
		EventDispatcher (){}
		void subscribe (std::weak_ptr < std::function<void (sharedEvtPtr e)>> callback, Priority p = Priority::NORMAL);
		void unsubscribe (std::weak_ptr < std::function<void (sharedEvtPtr e)>> callback);
		void dispatch (sharedEvtPtr e);
	private:
	};
}