#pragma once

#include "Core.h"

namespace Cyprium
{
	class CYPRIUM_API Application
	{
	public:
		Application();
		virtual ~Application();
	
		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

