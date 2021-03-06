#pragma once

#include "Cyprium/Core/Core.h"

#include "Cyprium/Events/Event.h"
#include "Cyprium/Events/ApplicationEvent.h"
#include "Cyprium/Core/Window.h"
#include "Cyprium/Core/LayerStack.h"

#include "Cyprium/Core/Timestep.h"

#include "Cyprium/ImGui/ImGuiLayer.h"

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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

