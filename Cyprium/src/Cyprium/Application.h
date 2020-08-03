#pragma once

#include "Cyprium/Core.h"

#include "Cyprium/Events/Event.h"
#include "Cyprium/Events/ApplicationEvent.h"
#include "Cyprium/Window.h"
#include "Cyprium/LayerStack.h"

namespace Cyprium
{
	class CYPRIUM_API Application
	{
	public:
		Application();
		virtual ~Application();
	
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

