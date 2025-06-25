#pragma once

#include "EngineInfo.h"

class CTimer
{
public:
    CTimer();
    ~CTimer();

private:
    float m_DeltaTime;
    float m_AccTime;
    unsigned long m_FPS;
    unsigned long m_FPSTick;
    unsigned long m_Tick;

public:
    bool Init();
    void Update();

    float GetDeltaTime() const 
    { 
        return m_DeltaTime; 
    }

    unsigned long GetFPS() const 
    { 
        return m_FPS; 
    }
};

