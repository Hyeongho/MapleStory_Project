#pragma once

#include "../Object/Object.h"
#include "../Actor/Actor.h"

class CScene :
    public CObject
{
public:
    CScene();
    virtual ~CScene();

    void Tick(float DeltaTime);
    void Render();

    void AddActor(const TSharedPtr<CActor>& Actor);
    const std::vector<TSharedPtr<CActor>>& GetActors() const;

private:
    std::vector<TSharedPtr<CActor>> m_Actors;
};

