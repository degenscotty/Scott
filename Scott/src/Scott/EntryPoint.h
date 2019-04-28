#pragma once

#ifdef SC_PLATFORM_WINDOWS

extern Scott::Application* Scott::CreateApplication();

int main(int argc, char** argv)
{
	printf("Scott Engine is Running!\n");
	auto app = Scott::CreateApplication();
	app->Run();
	delete app;
}


#endif