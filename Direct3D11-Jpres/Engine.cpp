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
	light = std::make_unique<PointLight>(graphics, 0.1f);

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

	//float r = (sin(timer.Peek()) / 2.0f) + 0.5f;
	//float g = (sin(timer.Peek() * 0.8f) / 2.0f) + 0.5f;
	//float b = (sin(timer.Peek() + 5.0f) / 2.0f) + 0.5f;


	graphics.ClearBuffer(0.1f, 0.1f, 0.1f, 1.0f);


	static float speedFactor = 0.001f;
	boxes[0]->Update(timer.Peek() * speedFactor);

	light->Bind(graphics);
	for (auto& box : boxes)
		box->Draw(graphics);

	for (auto& sheet : sheets)
		sheet->Draw(graphics);
	light->Draw(graphics);


	// imgui render

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (ImGui::Begin("Camera"))
	{
		ImGui::Text("FPS : %.1f", ImGui::GetIO().Framerate);
		ImGui::SliderFloat("Speed Factor", &speedFactor, 0.0f, 0.001f, "%.5f");


		// camera test
		static float pitch = 0.0f;
		static float roll = 0.0f;
		static float yaw = 0.0f;
		static float r = 4.0f;

		ImGui::Text("Position");
		ImGui::SliderFloat("r", &r, 0.1f, 80.0f, "%.1f");
		ImGui::SliderAngle("roll", &roll, -180.0f, 180.0f);
		ImGui::SliderAngle("pitch", &pitch, -180.0f, 180.0f);
		ImGui::SliderAngle("yaw", &yaw, -180.0f, 180.0f);
		if (ImGui::Button("Reset"))
		{
			pitch = 0.0f;
			roll = 0.0f;
			yaw = 0.0f;
			r = 4.0f;
		}

		graphics.SetCamera(DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
			DirectX::XMMatrixLookAtLH({ 0.0f, 0.0f, -r }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f })
		);


	}
	ImGui::End();

	light->SpawnControlWindow();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());



	graphics.EndFrame();
}
