#include "Engine.h"
#include "Device.h"
#include "Timer.h"
#include "GameInstance.h"

#include "Resource/Renderer/Renderer.h"

#include <crtdbg.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

DEFINITION_SINGLE(CEngine)

bool CEngine::m_Loop = true;

CEngine::CEngine() : m_hWnd(nullptr), m_hInst(nullptr)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    ZeroMemory(&m_RS, sizeof(m_RS));
}

CEngine::~CEngine()
{
    SAFE_DELETE(m_Timer);
    CDevice::DestroyInst();
}

bool CEngine::Init(HINSTANCE hInst, const TCHAR* Title, UINT Width, UINT Height, int IconID, bool WindowMode)
{
    m_hInst = hInst;
    m_RS = { Width, Height };

    // 윈도우 클래스 등록 및 메인 윈도우 생성
    RegisterWindowClass(Title, IconID);
    CreateMainWindow(Title);

    // CDevice 초기화
    if (!CDevice::GetInst()->Init(m_hWnd, m_RS.Width, m_RS.Height, WindowMode))
    {
        OutputDebugStringA("CDevice Init 실패\n");
        return false;
    }

    m_Timer = new CTimer;

    m_Renderer = new CRenderer;

    if (!m_Renderer->Init())
    {
        OutputDebugStringA("Renderer Init 실패\n");
        return false;
    }

    return true;
}

int CEngine::Run()
{
    MSG msg = {};

    while (m_Loop) 
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        else 
        {
            m_Timer->Update(); // 타이머 프레임 계산 (선택)

            CDevice::GetInst()->RenderStart();

            //CGameInstance::GetInst()->Update(m_Timer->GetDeltaTime()); // ← 선택 구현
            CGameInstance::GetInst()->Render(); // ← Scene → Actor → SpriteComponent → 삼각형

            CDevice::GetInst()->Flip();
        }
    }

    return (int)msg.wParam;
}

bool CEngine::Init(HINSTANCE hInst, HWND hWnd, UINT Width, UINT Height, bool WindowMode)
{
    m_hInst = hInst;
    m_hWnd = hWnd;
    m_RS = { Width, Height };

    //먼저 CDevice 생성 및 초기화
    if (!CDevice::GetInst()->Init(m_hWnd, m_RS.Width, m_RS.Height, WindowMode))
    {
        OutputDebugStringA("CDevice Init 실패\n");
        return false;
    }

    m_Timer = new CTimer;

    m_Renderer = new CRenderer;

    if (!m_Renderer->Init())
    {
        OutputDebugStringA("Renderer Init 실패\n");
        return false;
    }

    return true;
}

LRESULT CEngine::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) 
    {
    case WM_DESTROY:
        m_Loop = false;
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

ATOM CEngine::RegisterWindowClass(const TCHAR* Name, int IconID)
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = m_hInst;
    wc.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IconID));
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = Name;
    wc.hIconSm = wc.hIcon;
    return RegisterClassEx(&wc);
}

BOOL CEngine::CreateMainWindow(const TCHAR* Name)
{
    m_hWnd = CreateWindow(Name, Name, WS_OVERLAPPEDWINDOW, 0, 0, m_RS.Width, m_RS.Height, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)
    {
        return FALSE;
    }

    RECT rc = { 0, 0, (LONG)m_RS.Width, (LONG)m_RS.Height };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);

    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

    return TRUE;
}
