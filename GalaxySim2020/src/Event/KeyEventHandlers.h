#pragma once
#include "Corepch.h"
#include "BaseClasses/EventHandlers.h"
#include "KeyEvents.h"

namespace Application
{
	/// <summary>
	/// Key events will always be processed as their most specific type first
	/// and then propogate if event::handle() is not called.
	/// </summary>
	class KeyEventHandler : public EventHandler
	{
		virtual void onEvent (Event* e) override
		{
			if ( e->getEventCategory () & EventCategory::CatKeyEvent )
				switch ( e->getEventType())
				{
					case EventType::KeyPressed:
						onKeyPressed (dynamic_cast<KeyPressedEvent*>(e));
						if ( e->isHandled () )
							break;
					case EventType::KeyReleased:
						onKeyReleased (dynamic_cast<KeyReleasedEvent*>(e));
						if ( e->isHandled () )
							break;
					default:
						onKeyEvent (dynamic_cast<KeyEvent*>(e));
						break;
				}
		};
		virtual void onKeyEvent (KeyEvent* e) {};
		virtual void onKeyPressed (KeyPressedEvent* e) {};
		virtual void onKeyReleased (KeyReleasedEvent* e) {};

	};
	
}