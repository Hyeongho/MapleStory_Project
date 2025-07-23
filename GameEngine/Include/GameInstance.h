#pragma once

#include "Object/Object.h"
#include "World/World.h"

class CGameInstance
{
	DECLARE_SINGLE(CGameInstance)

private:
	TSharedPtr<CWorld> m_World;

public:
	void Init();
	void Tick(float DeltaTime);
	void Render();

	TSharedPtr<CWorld> GetWorld() const
	{ 
		return m_World; 
	}
};

