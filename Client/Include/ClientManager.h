#pragma once

#include"ClientInfo.h"

class CClientManager
{
private:
    HINSTANCE m_hInst;

public:
    bool Init(HINSTANCE hInst);
    int Run();
    void CreateDefaultSceneMode();  // 추후 확장 지점

    DECLARE_SINGLE(CClientManager)
};

