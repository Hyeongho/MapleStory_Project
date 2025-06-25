#pragma once

#include "EngineInfo.h"
#include "Timer.h"

class CTimer;

class CEngine
{

private:
    static bool m_Loop;

public:
    bool Init(HINSTANCE hInst, const TCHAR* Title, UINT Width, UINT Height, int IconID = 0, bool WindowMode = true);
    int Run();

private:
    bool Init(HINSTANCE hInst, HWND hWnd, UINT Width, UINT Height, bool WindowMode);
    bool InitDevice(bool WindowMode);

private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    ATOM RegisterWindowClass(const TCHAR* Name, int IconID);
    BOOL CreateMainWindow(const TCHAR* Name);

private:
    HINSTANCE m_hInst;
    HWND m_hWnd;
    Resolution m_RS;
    CTimer* m_Timer;

    class CRenderer* m_Renderer;

    DECLARE_SINGLE(CEngine)
};

