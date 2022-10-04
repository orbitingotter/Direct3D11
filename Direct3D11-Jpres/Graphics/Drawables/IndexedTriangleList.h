#pragma once

#include <vector>
#include <DirectXMath.h>
#include "Utilities/ErrorLogger.h"

template<typename T>
class IndexedTriangleList
{
public:
	IndexedTriangleList(std::vector<T> inVerts, std::vector<unsigned short> inIndices)
		: vertices(std::move(inVerts)), indices(std::move(inIndices))
	{
		if (vertices.size() < 2)
			ErrorLogger::Log("Vertices cannot be less than 2");
		else if (indices.size() % 3 != 0)
			ErrorLogger::Log("Indices must be in multiples of 3");
	}

	void Transform(DirectX::FXMMATRIX matrix)
	{
		for (auto& v : vertices)
		{
			const DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&v.pos);

			DirectX::XMStoreFloat3(&v.pos, DirectX::XMVector3Transform(pos, matrix));

		}
	}

	void SetNormalsIndependentFlat()
	{
		for (size_t i = 0; i < indices.size(); i+=3)
		{
			T& v0 = vertices[indices[i]];
			T& v1 = vertices[indices[i + 1]];
			T& v2 = vertices[indices[i + 2]];

			const DirectX::XMVECTOR p0 = DirectX::XMLoadFloat3(&v0.pos);
			const DirectX::XMVECTOR p1 = DirectX::XMLoadFloat3(&v1.pos);
			const DirectX::XMVECTOR p2 = DirectX::XMLoadFloat3(&v2.pos);

			const DirectX::XMVECTOR normal = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(DirectX::XMVectorSubtract(p1, p0),
				DirectX::XMVectorSubtract(p2, p0)));
			DirectX::XMStoreFloat3(&v0.normal, normal);
			DirectX::XMStoreFloat3(&v1.normal, normal);
			DirectX::XMStoreFloat3(&v2.normal, normal);

		}
	}

public:
	std::vector<T> vertices;
	std::vector<unsigned short> indices;
};