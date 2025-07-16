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

    // CEngine �ʱ�ȭ ȣ��
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
    // ���� SceneManager ���� ���� �ʱ� ��/��� ����
    // ��: CSceneManager::GetInst()->ChangeScene(...);
}