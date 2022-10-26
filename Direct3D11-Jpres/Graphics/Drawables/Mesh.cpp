#include "Mesh.h"

#include <DirectXMath.h>

#include "Graphics/Bindables/BindableIncludes.h"
#include "Graphics/Drawables/Primitives/Cube.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


Mesh::Mesh(Graphics& gfx)
{
	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT3 normal;
		};

		Assimp::Importer imp;
		const aiScene* model = imp.ReadFile("Resources/utah-teapot.stl", aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

		const auto pMesh = model->mMeshes[0];

		std::vector<Vertex> vertices;
		vertices.reserve(pMesh->mNumVertices);
		for (unsigned int i = 0; i < pMesh->mNumVertices; i++)
		{
			vertices.push_back({ *reinterpret_cast<DirectX::XMFLOAT3*>(&pMesh->mVertices[i]),
				*reinterpret_cast<DirectX::XMFLOAT3*>(&pMesh->mNormals[i]) });
		}

		std::vector<unsigned short> indices;
		indices.reserve(pMesh->mNumFaces * 3);

		for (unsigned short i = 0; i < pMesh->mNumFaces; i++)
		{
			const auto pFace = pMesh->mFaces[i];
			indices.push_back(pFace.mIndices[0]);
			indices.push_back(pFace.mIndices[1]);
			indices.push_back(pFace.mIndices[2]);

		}

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertices));
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, indices));

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

void Mesh::Update(float dt)
{
	roll += dRoll * dt;
	//pitch += dPitch * dt;
	//yaw += dYaw * dt;

	//theta += dTheta * dt;
	//phi += dPhi * dt;
	//chi += dChi * dt;
}


DirectX::XMMATRIX Mesh::GetTransformXM() const
{
	float scale = 1.0f;
	return
		DirectX::XMMatrixScaling(scale, scale, scale) *
		DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(r, 0.0f, 0.0f) *
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi);
}
