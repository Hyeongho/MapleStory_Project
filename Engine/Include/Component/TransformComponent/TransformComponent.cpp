#include "TransformComponent.h"

CTransformComponent::CTransformComponent() : m_Position(0.f, 0.f), m_Scale(1.f, 1.f), m_Rotation(0.f)
{
}

CTransformComponent::~CTransformComponent() = default;

void CTransformComponent::Tick(float DeltaTime)
{
	CComponent::Tick(DeltaTime);

	// ���� �ִϸ��̼�, ���� ���� �� ��ġ ���� �� ó�� ����
	// ��: m_Position += m_Velocity * DeltaTime;
}
