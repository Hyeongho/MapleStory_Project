#pragma once

#include "../Object/Object.h"
#include "Scene.h"

class CWorld :
    public CObject
{
public:
    CWorld();
    virtual ~CWorld();

    void Init();
    void Tick(float DeltaTime);
    void Render();

    void SetCurrentScene(const TSharedPtr<CScene>& Scene);
    const TSharedPtr<CScene>& GetCurrentScene() const;

private:
    TSharedPtr<CScene> m_CurrentScene;
};

