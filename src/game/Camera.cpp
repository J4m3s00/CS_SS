#include "prefix.h"

FpsCamera::FpsCamera()
    : fDirty(true)
{

}

const DirectX::XMMATRIX& FpsCamera::GetViewMatrix() const 
{
    if (fDirty)
        UpdateViewMatrix();
    return fViewMatrix;
}

void FpsCamera::Update(float delta)
{

}

void FpsCamera::UpdateViewMatrix()
{
    
    fDirty = false;
}