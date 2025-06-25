#include "Device.h"
#include <cassert>

DEFINITION_SINGLE(CDevice)

CDevice::CDevice() 
{

}

CDevice::~CDevice() 
{

}

bool CDevice::Init(HWND hWnd, UINT Width, UINT Height, bool WindowMode)
{
    m_hWnd = hWnd;
    m_RS = { Width, Height };
    m_WindowMode = WindowMode;

    DXGI_SWAP_CHAIN_DESC swapDesc = {};
    swapDesc.BufferCount = 1;
    swapDesc.BufferDesc.Width = Width;
    swapDesc.BufferDesc.Height = Height;
    swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapDesc.OutputWindow = hWnd;
    swapDesc.SampleDesc.Count = 1;
    swapDesc.Windowed = WindowMode;
    swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT deviceFlags = 0;
#ifdef _DEBUG
    deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevel;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        deviceFlags,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapDesc,
        &m_SwapChain,
        &m_Device,
        &featureLevel,
        &m_Context
    );

    if (FAILED(hr)) 
    {
        assert(false && "D3D11CreateDeviceAndSwapChain Failed");
        return false;
    }

    // ¹é¹öÆÛ -> ·»´õ Å¸°Ù ºä »ý¼º
    ComPtr<ID3D11Texture2D> backBuffer;
    m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
    m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_RenderTargetView.GetAddressOf());

    D3D11_VIEWPORT vp = {};
    vp.Width = static_cast<FLOAT>(m_RS.Width);
    vp.Height = static_cast<FLOAT>(m_RS.Height);
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    m_Context->RSSetViewports(1, &vp);

    return true;
}

void CDevice::RenderStart()
{
    float clearColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
    m_Context->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), nullptr);
    m_Context->ClearRenderTargetView(m_RenderTargetView.Get(), clearColor);
}

void CDevice::Flip()
{
    m_SwapChain->Present(1, 0);
}
