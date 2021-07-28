#pragma once
#include "Corepch.h"
namespace Application
{
	class Layer
	{
	
	public:
		virtual void onAttach () = 0;
		virtual void onDetatch () = 0;
		virtual bool init () = 0;
	};
}