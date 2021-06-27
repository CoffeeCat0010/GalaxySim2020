#pragma once
namespace Application
{
	class Layer
	{
	
	public:
		virtual void onAttach () = 0;
		virtual void onDetatch () = 0;
	};
}