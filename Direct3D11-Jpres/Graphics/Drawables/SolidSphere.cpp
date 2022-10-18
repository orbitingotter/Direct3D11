#include "SolidSphere.h"

#include "Graphics/Bindables/BindableIncludes.h"
#include "Graphics/Drawables/Primitives/Sphere.h"


SolidSphere::SolidSphere(Graphics& gfx, float radius)
{
	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
		};
		auto model = Sphere::MakeTesselated<Vertex>(12, 24);
		model.Transform(DirectX::XMMatrixScaling(radius, radius, radius));
		AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));

		auto vs = std::make_unique<VertexShader>(gfx, "Shaders/SolidVS.cso");
		auto pvsbc = vs->GetByteCode();
		AddStaticBind(std::move(vs));

		AddStaticBind(std::make_unique<PixelShader>(gfx, "Shaders/SolidPS.cso"));

		struct PSColorConstant
		{
			DirectX::XMFLOAT3 color = { 1.0f,1.0f,1.0f };
			float padding;
		} colorConst;

		AddStaticBind(std::make_unique<PixelConstantBuffer<PSColorConstant>>(gfx, colorConst));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

		AddStaticBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}

	AddBind(std::make_unique<TransformCBuf>(gfx, *this));
}

void SolidSphere::Update(float dt)
{
}

void SolidSphere::SetPos(DirectX::XMFLOAT3 pos)
{
	mPos = pos;
}

DirectX::XMMATRIX SolidSphere::GetTransformXM() const
{
	return DirectX::XMMatrixTranslation(mPos.x, mPos.y, mPos.z);
}