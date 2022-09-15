#include "Sheet.h"

#include <DirectXMath.h>
#include "DrawableIncludes.h"

Sheet::Sheet(Graphics& gfx)
{
	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			float x, y, z;
			float u, v;
		};

		std::vector<Vertex> vertices =
		{
			{-0.5f, -0.5f, 0.0f, 0.0f, 1.0f},
			{-0.5f, 0.5f, 0.0f, 0.0f, 0.0f},
			{0.5f, -0.5f, 0.0f, 1.0f, 1.0f},
			{0.5f, 0.5f, 0.0f, 1.0f, 0.0f}
		};

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertices));

		const std::vector<unsigned short> indices =
		{
			0,1,2,
			2,1,3
		};

		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, indices));

		AddStaticBind(std::make_unique<Texture>(gfx, "Resources\\howl.png"));
		AddStaticBind(std::make_unique<Sampler>(gfx));

		auto vs = std::make_unique<VertexShader>(gfx, "TextureVS.cso");
		auto pvsbc = vs->GetByteCode();
		AddStaticBind(std::move(vs));

		AddStaticBind(std::make_unique<PixelShader>(gfx, "TexturePS.cso"));

		std::vector<D3D11_INPUT_ELEMENT_DESC> layout =
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};

		AddStaticBind(std::make_unique<InputLayout>(gfx, layout, pvsbc));

		AddStaticBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}

	AddBind(std::make_unique<TransformCBuf>(gfx, *this));
}

void Sheet::Update(float dt)
{
	roll += dRoll * dt;
	pitch += dPitch * dt;
	yaw += dYaw * dt;

	theta += dTheta * dt;
	phi += dPhi * dt;
	chi += dChi * dt;
}

DirectX::XMMATRIX Sheet::GetTransformXM() const
{
	return
		DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f) *
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
		DirectX::XMMatrixScaling(2.0f, 2.0f, 1.0f) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 2.0f);
}
