#include "Engine.h"
#include "Utilities/ErrorLogger.h"


#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"


bool Engine::Initialize(std::string windowTitle, std::string windowClass, int width, int height)
{
	if (!renderWindow.Initialize(this, windowTitle, windowClass, width, height))
	{
		return false;
	}

	if (!graphics.Initialize(renderWindow.GetHandle(), width, height))
	{
		return false;
	}

	boxes.push_back(std::make_unique<Box>(graphics));
	//sheets.push_back(std::make_unique<Sheet>(graphics));

	graphics.SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, (float)((float)height / (float)width), 0.5f, 40.0f));

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

	for (auto& sheet : sheets)
		sheet->Draw(graphics);

	//graphics.DrawTriangleNew(timer.Peek() * 0.2f);


	// imgui render

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	static bool showDemo = true;
	if (showDemo)
	{
		ImGui::ShowDemoWindow(&showDemo);
	}
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());



	graphics.EndFrame();
}
