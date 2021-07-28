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
		static EventDispatcher* INSTANCE;
		std::vector<std::weak_ptr<std::function<void(Event* e)>>> m_callbacks;
	public:
		static const enum class Priority { CRITICAL, NORMAL };
		EventDispatcher (){}
		void subscribe (std::weak_ptr < std::function<void (Event* e)>> callback, Priority p = Priority::NORMAL);
		void unsubscribe (std::weak_ptr < std::function<void (Event* e)>> callback);
		void dispatch (Event* e);
	private:
	};
}