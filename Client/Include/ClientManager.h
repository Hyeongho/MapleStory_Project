#pragma once

#include"ClientInfo.h"

class CClientManager
{
private:
    HINSTANCE m_hInst;

public:
    bool Init(HINSTANCE hInst);
    int Run();
    void CreateDefaultSceneMode();  // ���� Ȯ�� ����

    DECLARE_SINGLE(CClientManager)
};

