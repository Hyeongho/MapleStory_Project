#include "World.h"

CWorld::CWorld() = default;
CWorld::~CWorld() = default;

void CWorld::Init() 
{
    // �⺻ �� ���� �Ǵ� �ε�
}

void CWorld::Tick(float DeltaTime) 
{
    if (IsValid(m_CurrentScene))
    {
        m_CurrentScene->Tick(DeltaTime);
    }
}

void CWorld::Render() 
{
    if (IsValid(m_CurrentScene))
    {
        m_CurrentScene->Render();
    }
}

void CWorld::SetCurrentScene(const TSharedPtr<CScene>& Scene)
{
    m_CurrentScene = Scene;
}

const TSharedPtr<CScene>& CWorld::GetCurrentScene() const
{
    return m_CurrentScene;
}