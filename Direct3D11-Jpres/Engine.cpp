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
	graphics.SetCamera(DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f));

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

	static float speedFactor = 0.001;
	boxes[0]->Update(timer.Peek() * speedFactor);

	for (auto& box : boxes)
		box->Draw(graphics);

	for (auto& sheet : sheets)
		sheet->Draw(graphics);

	// imgui render

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (ImGui::Begin("Test"))
	{
		ImGui::Text("FPS : %.1f", ImGui::GetIO().Framerate);
		ImGui::SliderFloat("Speed Factor", &speedFactor, 0.0f, 0.001f, "%.5f", 1.0f);
	}
	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());



	graphics.EndFrame();
}
