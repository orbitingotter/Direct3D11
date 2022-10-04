#include "Box.h"

#include <DirectXMath.h>

#include "Graphics/Bindables/BindableIncludes.h"
#include "Graphics/Drawables/Primitives/Cube.h"

Box::Box(Graphics& gfx)
{
	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT3 normal;
		};

		IndexedTriangleList<Vertex> model = Cube::MakeIndependent<Vertex>();
		model.SetNormalsIndependentFlat();

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));

		auto vs = std::make_unique<VertexShader>(gfx, "Shaders/PhongVS.cso");
		auto pvsbc = vs->GetByteCode();
		AddStaticBind(std::move(vs));

		AddStaticBind(std::make_unique<PixelShader>(gfx, "Shaders/PhongPS.cso"));


		std::vector<D3D11_INPUT_ELEMENT_DESC> layout =
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};

		AddStaticBind(std::make_unique<InputLayout>(gfx, layout, pvsbc));

		AddStaticBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}

	AddBind(std::make_unique<TransformCBuf>(gfx, *this));
}

void Box::Update(float dt)
{
	roll += dRoll * dt;
	pitch += dPitch * dt;
	yaw += dYaw * dt;

	theta += dTheta * dt;
	phi += dPhi * dt;
	chi += dChi * dt;
}


DirectX::XMMATRIX Box::GetTransformXM() const
{

	return
		DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(r, 0.0f, 0.0f) *
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi)
		;
}
