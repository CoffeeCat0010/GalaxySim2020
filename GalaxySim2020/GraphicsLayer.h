#pragma once
#include "Corepch.h"
#include "Layers/Layer.h"
#include "Event/BaseClasses/EventHandlers.h"
#include "Event/BaseClasses/EventBroadcaster.h"

namespace Graphics{
	class GraphicsLayer: public Application::Layer, public Application::EventHandler
	{
	public:
		GraphicsLayer(std::shared_ptr<Application::EventBroadcaster> evtSystem);
		void onAttach() override;
		void onDetatch() override;
		void onEvent(Application::Event* e) override;
	private:
		void init();
	};
}

