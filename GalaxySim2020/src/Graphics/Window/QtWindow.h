#pragma once
#include "Corepch.h"
#include <qwindow.h>
#include "Window.h"

namespace Graphics
{
	class QtWindow : public QWindow, public IWindow
	{

		QtWindow (const std::string& name, int32_t sizeX, int32_t sizeY);
		QtWindow (const char* name, int32_t sizeX, int32_t sizeY);
		~QtWindow ();
		void pollEvents () override;

	};
}

