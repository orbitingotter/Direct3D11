#pragma once

#include "WindowContainer.h"
#include "Timer.h"

class Engine : public WindowContainer
{
public:
	bool Initialize(std::string window_title, std::string window_class, int width, int height);
	bool ProcessMessages();
	void Update();

private:

	Timer timer;
};