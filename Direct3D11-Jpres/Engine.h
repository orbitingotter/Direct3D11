#pragma once

#include "WindowContainer.h"
#include "Timer.h"
#include "Box.h"
#include "Sheet.h"
#include <memory>

class Engine : public WindowContainer
{
public:
	bool Initialize(std::string window_title, std::string window_class, int width, int height);
	bool ProcessMessages();
	void Update();

private:

	std::vector<std::unique_ptr<Box>> boxes;
	std::vector<std::unique_ptr<Sheet>> sheets;

	Timer timer;
};