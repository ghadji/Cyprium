#pragma once

#include "Cyprium/Core.h"
#include "Cyprium/Events/Event.h"
#include "Cyprium/Window.h"

namespace Cyprium
{
	class CYPRIUM_API Application
	{
	public:
		Application();
		virtual ~Application();
	
		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

