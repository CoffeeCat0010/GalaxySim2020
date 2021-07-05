#pragma once
#include "Corepch.h"
#include "Event.h"

namespace Application
{
	class EventHandler
	{
	public:
		virtual void onEvent (Event& e) = 0;
	};
}