#pragma once

#ifdef LT_PLATFORM_WINDOWS

extern Light::Application* Light::CreateApplication();

int main(int argc, char** argv)
{
	auto application = Light::CreateApplication();
	application->GameLoop();
	delete application;
}

#endif