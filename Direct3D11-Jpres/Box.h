#pragma once

#include "Drawable.h"


class Box : public Drawable
{
public:

	Box(Graphics& gfx);
	void Update(float dt) override;
	DirectX::XMMATRIX GetTransformXM() const override;

private:
	// Position
	float r = 0.0f;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta = 0.0f;
	float phi = 0.0f;
	float chi = 0.0f;
	// Speed
	float dRoll = 1.0f;
	float dPitch = 1.0f;
	float dYaw = 1.0f;
	float dTheta = 1.0f;
	float dPhi = 1.0f;
	float dChi = 1.0f;
};

