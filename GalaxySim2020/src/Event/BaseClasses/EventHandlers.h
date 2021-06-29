#pragma once
#include "Corepch.h"
#include "Event.h"

namespace Application
{
	class EventHandler
	{
		virtual void onEvent (Event e) = 0;
	};
	class KeyEventHandler: public EventHandler
	{
		virtual void onEvent (Event e) override = 
		{

		};
		virtual void onKeyPressed( MouseEvent)


	};
	class MouseEventHandler: public EventHandler
	{
		virtual void onEvent (Event e) = 0;
	}; 
	class GUIEventHandler: public EventHandler
	{
		virtual void onEvent (Event e) = 0;
	};
}