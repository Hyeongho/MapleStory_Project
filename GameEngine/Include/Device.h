#pragma once

#include "EngineInfo.h"

class CDevice
{
private:
    HWND m_hWnd;
    Resolution m_RS;
    bool m_WindowMode;

    ComPtr<ID3D11Device> m_Device;
    ComPtr<ID3D11DeviceContext> m_Context;
    ComPtr<IDXGISwapChain> m_SwapChain;
    ComPtr<ID3D11RenderTargetView> m_RenderTargetView;

public:
    bool Init(HWND hWnd, UINT Width, UINT Height, bool WindowMode);

    void RenderStart();   // ȭ�� �ʱ�ȭ
    void Flip();          // ȭ�� ���

    ID3D11Device* GetDevice() const 
    { 
        return m_Device.Get(); 
    }

    ID3D11DeviceContext* GetContext() const 
    { 
        return m_Context.Get(); 
    }

    DECLARE_SINGLE(CDevice)
};

