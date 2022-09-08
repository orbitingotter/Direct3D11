#include "Box.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Topology.h"
#include "InputLayout.h"
#include "TransformCBuf.h"

#include <DirectXMath.h>

Box::Box(Graphics& gfx)
{
	struct Vertex
	{
		float x, y, z;
		unsigned char r, g, b, a;
	};
	std::vector<Vertex> vertices =
	{
		{ -1.0f,-1.0f,-1.0f, 255, 0,0,255},
		{ 1.0f,-1.0f,-1.0f, 0,255,0,255},
		{ -1.0f,1.0f,-1.0f, 0,0,255,255},
		{ 1.0f,1.0f,-1.0f, 255, 255, 0,255},
		{ -1.0f,-1.0f,1.0f, 255,0,255,255},
		{ 1.0f,-1.0f,1.0f,0,255,255,255},
		{ -1.0f,1.0f,1.0f,255,255,255,255},
		{ 1.0f,1.0f,1.0f,0,0,0,255},
	};

	AddBind(std::make_unique<VertexBuffer>(gfx, vertices));

	const std::vector<unsigned short> indices =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};

	AddIndexBuffer(std::make_unique<IndexBuffer>(gfx, indices));

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));

	auto vs = std::make_unique<VertexShader>(gfx, "VertexShader.cso");
	auto pvsbc = vs->GetByteCode();
	AddBind(std::move(vs));

	AddBind(std::make_unique<PixelShader>(gfx, "PixelShader.cso"));

	std::vector<D3D11_INPUT_ELEMENT_DESC> layout =
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"Color", 0, DXGI_FORMAT_B8G8R8A8_UNORM, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	AddBind(std::make_unique<InputLayout>(gfx, layout, pvsbc));

	AddBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));


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
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f);
}
