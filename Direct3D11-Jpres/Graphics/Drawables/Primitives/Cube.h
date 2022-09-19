#pragma once

#include "Graphics/Drawables/IndexedTriangleList.h"

class Cube
{
public:
	template<typename T>
	static IndexedTriangleList<T> MakeBlend()
	{
		std::vector<T> vertices;

		vertices.emplace_back(T({ -1.0f, -1.0f, -1.0f }, { 255,0,0, 255 }));
		vertices.emplace_back(T({ 1.0f, -1.0f, -1.0f }, { 0, 255, 0, 255 }));
		vertices.emplace_back(T({ -1.0f, 1.0f, -1.0f }, { 0, 0, 255, 255 }));
		vertices.emplace_back(T({ 1.0f, 1.0f, -1.0f }, { 255, 255, 0, 255 }));
		vertices.emplace_back(T({ -1.0f, -1.0f, 1.0f }, { 255, 0, 255, 255 }));
		vertices.emplace_back(T({ 1.0f, -1.0f, 1.0f }, { 0, 255, 255, 255 }));
		vertices.emplace_back(T({ -1.0f, 1.0f, 1.0f }, { 255, 255, 255, 255 }));
		vertices.emplace_back(T({ 1.0f, 1.0f, 1.0f }, { 0, 0, 0, 255 }));

		const std::vector<unsigned short> indices =
		{
			0,2,1, 2,3,1,
			1,3,5, 3,7,5,
			2,6,3, 3,6,7,
			4,5,7, 4,7,6,
			0,4,2, 2,4,6,
			0,1,4, 1,5,4
		};

		return { std::move(vertices), std::move(indices) };

	}
};