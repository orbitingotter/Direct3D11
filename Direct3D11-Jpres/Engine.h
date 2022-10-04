#pragma once

#include "WindowContainer.h"
#include "Utilities/Timer.h"
#include "Graphics/PointLight.h"
#include "Graphics/Drawables/Box.h"
#include "Graphics/Drawables/Sheet.h"
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
	std::unique_ptr<PointLight> light;

	Timer timer;
};