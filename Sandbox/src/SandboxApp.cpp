#include <Cyprium.h>

class ExampleLayer : public Cyprium::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		CP_INFO("ExampleLayer::Update");
	}
	
	void OnEvent(Cyprium::Event& event) override
	{
		CP_TRACE("{0}", event);
	}
};

class Sandbox : public Cyprium::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Cyprium::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};

Cyprium::Application* Cyprium::CreateApplication()
{
	return new Sandbox();
}