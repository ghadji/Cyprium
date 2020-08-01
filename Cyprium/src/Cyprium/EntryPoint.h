#pragma once
#include <stdio.h>

#ifdef CP_PLATFORM_WINDOWS

extern Cyprium::Application* Cyprium::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Cyprium::CreateApplication();
	app->Run();
	delete app;
}

#endif