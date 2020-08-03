#include "cppch.h"
#include "Application.h"

#include "Cyprium/Events/ApplicationEvents.h"
#include "Cyprium/Log.h"

namespace Cyprium
{

	Application::Application()
	{}

	Application::~Application()
	{}

	void Application::Run()
	{
		WindowResizeEvent e(1200, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			CP_TRACE(e);
		}

		while(true);
	}
}