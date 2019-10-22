#pragma once

//Camera interface
class Camera
{
public:
	virtual const DirectX::XMMATRIX& GetViewMatrix() const = 0;

	virtual void Update(float delta) = 0;
};

class FpsCamera : public Camera
{
public:
	FpsCamera();

	virtual const DirectX::XMMATRIX& GetViewMatrix() const override;
	virtual void Update(float delta) override;
private:
	DirectX::XMMATRIX fViewMatrix;

	DirectX::XMVECTOR fPosition;
	DirectX::XMVECTOR fRotation;
};