#include "Scene.h"

CScene::CScene() = default;
CScene::~CScene() = default;

void CScene::Tick(float DeltaTime) 
{
    for (auto& Actor : m_Actors) 
    {
        if (IsValid(Actor) && !Actor->IsPendingDestroy())
        {
            Actor->Tick(DeltaTime);
        }
    }
}

void CScene::Render() 
{
    for (auto& Actor : m_Actors) 
    {
        if (IsValid(Actor) && !Actor->IsPendingDestroy())
        {
            Actor->Render();
        }
    }
}

void CScene::AddActor(const TSharedPtr<CActor>& Actor) 
{
    m_Actors.push_back(Actor);
}

const std::vector<TSharedPtr<CActor>>& CScene::GetActors() const 
{
    return m_Actors;
}