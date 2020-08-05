#include <Cyprium.h>

#include "imgui/imgui.h"

class ExampleLayer : public Cyprium::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	
	}

	void OnUpdate() override
	{
		// CP_INFO("ExampleLayer::Update"); 

		if (Cyprium::Input::IsMouseButtonPressed(CP_KEY_TAB))
			CP_TRACE("You've pressed the TAB Key!");
	}
	
	virtual void OnImGuiRender() override
	{
		//ImGui::Begin("Test");
		//ImGui::Text("Hello World!");
		//ImGui::End();
	}

	void OnEvent(Cyprium::Event& event) override
	{
		// CP_TRACE("{0}", event);
	}
};

class Sandbox : public Cyprium::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

Cyprium::Application* Cyprium::CreateApplication()
{
	return new Sandbox();
}