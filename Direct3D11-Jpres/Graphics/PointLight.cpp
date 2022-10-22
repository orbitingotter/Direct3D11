#include "PointLight.h"
#include "imgui/imgui.h"

PointLight::PointLight(Graphics& gfx, float radius)
	:
	mesh(gfx, radius), cbuf(gfx)
{
	Reset();
}

void PointLight::SpawnControlWindow() noexcept
{
	if (ImGui::Begin("Light"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &cbData.pos.x, -30.0f, 30.0f, "%.01f");
		ImGui::SliderFloat("Y", &cbData.pos.y, -30.0f, 30.0f, "%.01f");
		ImGui::SliderFloat("Z", &cbData.pos.z, -30.0f, 30.0f, "%.01f");

		ImGui::Text("Intensity / Color");
		ImGui::ColorEdit3("Material Color", &cbData.materialColor.x);
		ImGui::ColorEdit3("Ambient", &cbData.ambient.x);
		ImGui::ColorEdit3("Diffuse", &cbData.diffuseColor.x);
		ImGui::SliderFloat("Diffuse Intensity", &cbData.diffuseIntensity, 0.0f, 1.0f, "%.01f");

		ImGui::Text("Attenuation");
		ImGui::SliderFloat("Constant", &cbData.attConst, 0.001f, 10.0f, "%.5f");
		ImGui::SliderFloat("Linear", &cbData.attLin, 0.001f, 10.0f, "%.5f");
		ImGui::SliderFloat("Quadratic", &cbData.attQuad, 0.001f, 10.0f, "%.5f");

		if (ImGui::Button("Reset"))
		{
			Reset();
		}
	}
	ImGui::End();
}

void PointLight::Reset() noexcept
{
	cbData.pos = { 0.0f, 0.f, 0.0f };
	cbData.materialColor = { 0.7f, 0.7f, 0.9f };
	cbData.ambient = { 0.2f, 0.2f, 0.2f };
	cbData.diffuseColor = { 1.0f, 1.0f, 1.0f };
	cbData.diffuseIntensity = 1.0f;
	cbData.attConst = 1.0f;
	cbData.attLin = 0.045f;
	cbData.attQuad = 0.0075f;
}

void PointLight::Draw(Graphics& gfx) const
{
	mesh.SetPos(cbData.pos);
	mesh.Draw(gfx);
}

void PointLight::Bind(Graphics& gfx, DirectX::FXMMATRIX view) const
{
	auto dataCopy = cbData;
	const auto pos = DirectX::XMLoadFloat3(&cbData.pos);
	DirectX::XMStoreFloat3(&dataCopy.pos, DirectX::XMVector3Transform(pos, view));
	cbuf.Update(gfx, dataCopy);
	cbuf.Bind(gfx);

}