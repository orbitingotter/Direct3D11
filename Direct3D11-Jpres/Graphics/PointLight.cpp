#include "PointLight.h"
#include "imgui/imgui.h"

PointLight::PointLight(Graphics& gfx, float radius)
	:
	mesh(gfx, radius), cbuf(gfx)
{}

void PointLight::SpawnControlWindow() noexcept
{
	if (ImGui::Begin("Light"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &pos.x, -30.0f, 30.0f, "%.01f");
		ImGui::SliderFloat("Y", &pos.y, -30.0f, 30.0f, "%.01f");
		ImGui::SliderFloat("Z", &pos.z, -30.0f, 30.0f, "%.01f");
		if (ImGui::Button("Reset"))
		{
			Reset();
		}
	}
	ImGui::End();
}

void PointLight::Reset() noexcept
{
	pos = { 0.0f,0.0f,0.0f };
}

void PointLight::Draw(Graphics& gfx) const
{
	mesh.SetPos(pos);
	mesh.Draw(gfx);
}

void PointLight::Bind(Graphics& gfx) const
{
	cbuf.Update(gfx, PointLightCBuf{ pos });
	cbuf.Bind(gfx);
}