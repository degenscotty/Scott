#pragma once

#define SDL_MAIN_HANDLED

#include <SDL.h>

#ifdef SC_PLATFORM_WINDOWS

extern Scott::Application* Scott::CreateApplication();

int main(int argc, char *argv[])
{
	Scott::Log::Init();
	SC_CORE_WARN("Initialized Log!");
	SC_CORE_INFO("Hello!");
	int a = 5;
	SC_INFO("Hello! Var={0}", a);

	auto app = Scott::CreateApplication();
	app->Run();
	delete app;

	return 0;
}


#endif