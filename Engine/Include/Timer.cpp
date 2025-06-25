#include "Timer.h"

CTimer::CTimer() : m_DeltaTime(0.f), m_AccTime(0.f), m_FPS(0), m_FPSTick(0), m_Tick(0)
{
}

CTimer::~CTimer()
{
}

bool CTimer::Init()
{
    m_Tick = GetTickCount64();
    return true;
}

void CTimer::Update()
{
    DWORD curTick = GetTickCount64();
    m_DeltaTime = (curTick - m_Tick) / 1000.f;
    m_Tick = curTick;

    m_AccTime += m_DeltaTime;
    m_FPSTick++;

    if (m_AccTime >= 1.f)
    {
        m_FPS = m_FPSTick;
        m_AccTime = 0.f;
        m_FPSTick = 0;
    }
}