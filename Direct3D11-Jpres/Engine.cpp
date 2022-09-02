#include "Engine.h"
#include "ErrorLogger.h"

bool Engine::Initialize(std::string windowTitle, std::string windowClass, int width, int height)
{
	if (!renderWindow.Initialize(this, windowTitle, windowClass, width, height))
	{
		return false;
	}

	if (!graphics.Initialize(renderWindow.GetHandle()))
	{
		return false;
	}

	return true;
}

bool Engine::ProcessMessages()
{
	return renderWindow.ProcessMessages();
}

void Engine::Update()
{
	//std::string text = std::to_string(mouse.GetPosX()) + ", " + std::to_string(mouse.GetPosY());
	//SetWindowTextA(renderWindow.GetHandle(), text.c_str());

	float r = (sin(timer.Peek()) / 2.0f) + 0.5f;
	float g = (sin(timer.Peek() * 0.8f) / 2.0f) + 0.5f;
	float b = (sin(timer.Peek() + 5.0f) / 2.0f) + 0.5f;


	graphics.ClearBuffer(r, g, b, 1.0f);
	graphics.DrawTriangle(timer.Peek() * 0.4f);

	graphics.EndFrame();
}
