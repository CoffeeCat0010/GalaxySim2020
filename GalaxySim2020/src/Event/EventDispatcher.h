#pragma once
#include "Corepch.h"
#include "BaseClasses/Event.h"
#include "BaseClasses/EventHandlers.h"
#include "BaseClasses/EventBroadcaster.h"

namespace Application
{

	class EventDispatcher : public EventBroadcaster
	{
	private:
		static EventDispatcher* INSTANCE;
		std::vector<std::weak_ptr<EventHandler>> m_handlers;
	public:
		static EventDispatcher* getInstance();
		void subscribe (std::weak_ptr < EventHandler > handler, Priority p = Priority::NORMAL) override;
		void unsubscribe (std::weak_ptr < EventHandler > handler) override;
		void upload (Event* e) override;
	private:
		EventDispatcher (){}
	};
}