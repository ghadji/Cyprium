#include <Cyprium.h>

class Sandbox : public Cyprium::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

Cyprium::Application* Cyprium::CreateApplication()
{
	return new Sandbox();
}