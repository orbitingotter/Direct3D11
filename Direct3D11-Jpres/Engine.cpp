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

	boxes.push_back(std::make_unique<Box>(graphics));


	graphics.SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));

	return true;
}

bool Engine::ProcessMessages()
{
	return renderWindow.ProcessMessages();
}

void Engine::Update()
{

	float r = (sin(timer.Peek()) / 2.0f) + 0.5f;
	float g = (sin(timer.Peek() * 0.8f) / 2.0f) + 0.5f;
	float b = (sin(timer.Peek() + 5.0f) / 2.0f) + 0.5f;


	graphics.ClearBuffer(r, g, b, 1.0f);

	boxes[0]->Update(timer.Peek() * 0.001f);

	for (auto& box : boxes)
		box->Draw(graphics);

	//graphics.DrawTriangleNew(timer.Peek() * 0.2f);

	graphics.EndFrame();
}
