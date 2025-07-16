#include "TransformComponent.h"

CTransformComponent::CTransformComponent() : m_Position(0.f, 0.f), m_Scale(1.f, 1.f), m_Rotation(0.f)
{
}

CTransformComponent::~CTransformComponent() = default;

void CTransformComponent::Tick(float DeltaTime)
{
	CComponent::Tick(DeltaTime);

	// 추후 애니메이션, 물리 연동 시 위치 갱신 등 처리 가능
	// 예: m_Position += m_Velocity * DeltaTime;
}
