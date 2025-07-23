#include "Actor.h"
#include "../Component/Component.h"

CActor::CActor() = default;

CActor::~CActor() = default;

void CActor::AddComponent(const TSharedPtr<CComponent>& Component)
{
    if (IsValid(Component))
    {
        Component->SetOwner(this);
        m_Components.push_back(Component);
    }
}

const std::vector<TSharedPtr<CComponent>>& CActor::GetComponents() const
{
	// TODO: 여기에 return 문을 삽입합니다.
    return m_Components;
}

void CActor::Tick(float DeltaTime)
{
    CObject::Tick(DeltaTime);

    for (const auto& Component : m_Components)
    {
        if (IsValid(Component) && !Component->IsPendingDestroy())
        {
            Component->Tick(DeltaTime);
        }
    }
}

void CActor::Render()
{
    CObject::Render();

    for (const auto& Component : m_Components)
    {
        if (IsValid(Component) && !Component->IsPendingDestroy())
        {
            Component->Render();
        }
    }
}
