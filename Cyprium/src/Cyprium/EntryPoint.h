#pragma once
#include <stdio.h>

#ifdef CP_PLATFORM_WINDOWS

extern Cyprium::Application* Cyprium::CreateApplication();

int main(int argc, char** argv)
{
	Cyprium::Log::Init();
	CP_CORE_WARN("Initialized Logger!");
	int a = 2;
	CP_INFO("Hello Var={0}!", a);

	auto app = Cyprium::CreateApplication();
	app->Run();
	delete app;
}

#endif