#include "ClientManager.h"
#include "Engine.h"

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
}