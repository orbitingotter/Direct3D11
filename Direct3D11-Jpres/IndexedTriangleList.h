#pragma once

#include <vector>
#include <DirectXMath.h>
#include "ErrorLogger.h"

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

public:
	std::vector<T> vertices;
	std::vector<unsigned short> indices;
};