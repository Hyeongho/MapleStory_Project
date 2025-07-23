#include "ClientManager.h"

#include "Engine.h"
#include "Device.h"
#include "GameInstance.h"

#include "World/World.h"
#include "World/Scene.h"
#include "Actor/Actor.h"
#include "Component/TransformComponent/TransformComponent.h"
#include "Component/SpriteComponent/SpriteComponent.h"
#include "Resource/Renderer/Renderer.h"

DEFINITION_SINGLE(CClientManager)

CClientManager::CClientManager() 
{
}

CClientManager::~CClientManager() 
{
}

bool CClientManager::Init(HINSTANCE hInst)
{
    m_hInst = hInst;

    // CEngine 초기화 호출
    if (!CEngine::GetInst()->Init(hInst, TEXT("Maple2D"), 1280, 720))
    {
        return false;
    }

    return true;
}

int CClientManager::Run()
{
    return CEngine::GetInst()->Run();
}

void CClientManager::CreateDefaultSceneMode()
{
    // 추후 SceneManager 등을 통해 초기 씬/모드 지정
    // 예: CSceneManager::GetInst()->ChangeScene(...);

    CGameInstance::GetInst()->Init(); 

    TSharedPtr<CWorld> world = CGameInstance::GetInst()->GetWorld();
    TSharedPtr<CScene> scene = world->GetCurrentScene();

    TSharedPtr<CActor> testActor = MakeShared<CActor>();

    TSharedPtr<CTransformComponent> transform = MakeShared<CTransformComponent>();

    if (IsValid(transform))
    {
        transform->SetPosition(Vector2(300.f, 300.f));
        testActor->AddComponent(Cast<CComponent>(transform));
    }

    TSharedPtr<CSpriteComponent> sprite = MakeShared<CSpriteComponent>();

    if (IsValid(sprite))
    {
        sprite->SetSize(Vector2(128.f, 128.f));

        testActor->AddComponent(Cast<CComponent>(sprite));
    } 

    scene->AddActor(testActor);
}