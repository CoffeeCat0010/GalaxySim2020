#pragma once
#include "Corepch.h"
#include "BaseClasses/EventHandlers.h"
#include "MouseEvents.h"
namespace Application
{
	class MouseEventHandler : public EventHandler
	{
		virtual void onEvent (Event* e) override
		{
			if ( e->getEventCategory () & EventCategory::CatMouseEvent )
				switch ( e->getEventType () )
				{
					case EventType::MousePressed:
						onMousePressed (dynamic_cast<MousePressedEvent*>(e));
						if ( e->isHandled () )
							break;
					case EventType::MouseReleased:
						onMouseReleased (dynamic_cast<MouseReleasedEvent*>(e));
						if ( e->isHandled () )
							break;
					case EventType::MouseScrolled:
						onMouseScroll (dynamic_cast<MouseScrollEvent*>(e));
						if ( e->isHandled () )
							break;
					default:
						onMouseEvent (dynamic_cast<MouseEvent*>(e));
						break;
				}
		};
		virtual void onMouseEvent (MouseEvent* e) {};
		virtual void onMousePressed (MousePressedEvent* e) {};
		virtual void onMouseReleased (MouseReleasedEvent* e) {};
		virtual void onMouseScroll (MouseScrollEvent* e) {};


	};
}