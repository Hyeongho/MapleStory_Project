#include "GameInstance.h"

#include "World/Scene.h"

DEFINITION_SINGLE(CGameInstance)

CGameInstance::CGameInstance()
{
	
}

CGameInstance::~CGameInstance()
{
	
}

void CGameInstance::Init()
{
	m_World = MakeShared<CWorld>();

	TSharedPtr<CScene> MainScene = MakeShared<CScene>();

	m_World->SetCurrentScene(MainScene);

	// TODO: �׽�Ʈ ���� �߰� ����
}

void CGameInstance::Tick(float DeltaTime)
{
	if (IsValid(m_World))
	{
		m_World->Tick(DeltaTime);
	}
}

void CGameInstance::Render()
{
	if (IsValid(m_World))
	{
		m_World->Render();
	}
}