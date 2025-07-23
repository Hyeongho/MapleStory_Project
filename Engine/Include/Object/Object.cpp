#include "Object.h"

CObject::CObject()
{
}

void CObject::Destroy()
{
	m_PendingDestroy = true;
}

void CObject::Tick(float DeltaTime)
{
}

void CObject::Render()
{
}
