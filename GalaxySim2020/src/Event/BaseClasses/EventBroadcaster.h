#pragma once
#include "Corepch.h"
#include "EventHandlers.h"
namespace Application
{
	class EventBroadcaster
	{
	public:
		static const enum class Priority { CRITICAL, NORMAL };
		virtual void subscribe (std::weak_ptr < EventHandler> handler, Priority p = Priority::NORMAL) = 0;
		virtual void unsubscribe (std::weak_ptr<EventHandler> handler)= 0;
		virtual void upload(Event* e) = 0;
		virtual void broadcast() {};
	};
}