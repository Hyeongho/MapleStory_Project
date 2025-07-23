#include "Renderer.h"
#include "../../Device.h"

CRenderer::CRenderer()
{
}

CRenderer::~CRenderer()
{
}

bool CRenderer::Init()
{
    ID3D11Device* device = CDevice::GetInst()->GetDevice();

    if (!device)
    {
        OutputDebugStringA("Device is null in CRenderer::Init()\n");
        return false;
    }

    // 정점 데이터
    Vertex vertices[] =
    {
        { { 0.0f,  0.5f, 0.0f }, { 1.f, 0.f, 0.f, 1.f } },
        { { 0.5f, -0.5f, 0.0f }, { 0.f, 1.f, 0.f, 1.f } },
        { { -0.5f, -0.5f, 0.0f }, { 0.f, 0.f, 1.f, 1.f } }
    };

    // 버텍스 버퍼 생성
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(vertices);  //  명확하게 계산
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertices;

    HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, m_VertexBuffer.GetAddressOf());

    if (FAILED(hr))
    {
        OutputDebugStringA("Failed to create vertex buffer in CRenderer::Init()\n");
        return false;
    }

    std::vector<char> vsBytecode;
    if (!LoadShaderFromFile("../Bin/VertexShader.cso", vsBytecode))
    {
        OutputDebugStringA("Failed to Load VertexShader\n");

        return false;
    }

    hr = device->CreateVertexShader(vsBytecode.data(), vsBytecode.size(), nullptr, m_VertexShader.GetAddressOf());
    if (FAILED(hr)) 
    {
        return false;
    }

    std::vector<char> psBytecode;
    if (!LoadShaderFromFile("../Bin/PixelShader.cso", psBytecode))
    {
        OutputDebugStringA("Failed to Load PixelShader\n");

        return false;
    }

    hr = device->CreatePixelShader(psBytecode.data(), psBytecode.size(), nullptr, m_PixelShader.GetAddressOf());
    if (FAILED(hr)) 
    {
        return false;
    }

    // Input Layout 정의
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,                          D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(float) * 3,          D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    hr = device->CreateInputLayout(layout, ARRAYSIZE(layout), vsBytecode.data(), vsBytecode.size(), m_InputLayout.GetAddressOf());

    if (FAILED(hr))
    {
        return false;
    }

    // Sprite 셰이더 로딩
    std::vector<char> spriteVS, spritePS;
    if (!LoadShaderFromFile("../Bin/SpriteVertexShader.cso", spriteVS)) 
    {
        return false;
    }

    if (!LoadShaderFromFile("../Bin/SpritePixelShader.cso", spritePS)) 
    {
        return false;
    }

    hr = device->CreateVertexShader(spriteVS.data(), spriteVS.size(), nullptr, m_SpriteVertexShader.GetAddressOf());

    if (FAILED(hr))
    {
        return false;
    }

    hr = device->CreatePixelShader(spritePS.data(), spritePS.size(), nullptr, m_SpritePixelShader.GetAddressOf());

    if (FAILED(hr))
    {
        return false;
    }

    D3D11_INPUT_ELEMENT_DESC spriteLayout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    hr = device->CreateInputLayout(spriteLayout, 2, spriteVS.data(), spriteVS.size(), m_SpriteInputLayout.GetAddressOf());

    if (FAILED(hr))
    {
        return false;
    }

    D3D11_SAMPLER_DESC sampDesc = {};
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

    hr = device->CreateSamplerState(&sampDesc, m_SamplerState.GetAddressOf());

    if (FAILED(hr))
    {
        return false;
    }

    return true;
}

void CRenderer::Render()
{
    ID3D11DeviceContext* context = CDevice::GetInst()->GetContext();

    // 정점 버퍼 설정
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    context->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // 인풋 레이아웃 및 셰이더 설정
    context->IASetInputLayout(m_InputLayout.Get());
    context->VSSetShader(m_VertexShader.Get(), nullptr, 0);
    context->PSSetShader(m_PixelShader.Get(), nullptr, 0);

    context->Draw(3, 0);
}

void CRenderer::DrawSprite(ID3D11ShaderResourceView* texture, const Vector2& position, const Vector2& size)
{
    ID3D11DeviceContext* context = CDevice::GetInst()->GetContext();

    float l = position.x;
    float t = position.y;
    float r = position.x + size.x;
    float b = position.y + size.y;

    SpriteVertex vertices[] = {
        { { l, t, 0.f }, { 0.f, 0.f } },
        { { r, b, 0.f }, { 1.f, 1.f } },
        { { l, b, 0.f }, { 0.f, 1.f } },

        { { l, t, 0.f }, { 0.f, 0.f } },
        { { r, t, 0.f }, { 1.f, 0.f } },
        { { r, b, 0.f }, { 1.f, 1.f } },
    };

    D3D11_BUFFER_DESC vbDesc = { sizeof(vertices), D3D11_USAGE_IMMUTABLE, D3D11_BIND_VERTEX_BUFFER };
    D3D11_SUBRESOURCE_DATA vbData = { vertices };
    ComPtr<ID3D11Buffer> vertexBuffer;
    HRESULT hr = CDevice::GetInst()->GetDevice()->CreateBuffer(&vbDesc, &vbData, vertexBuffer.GetAddressOf());

    if (FAILED(hr)) 
    {
        return;
    }

    UINT stride = sizeof(SpriteVertex);
    UINT offset = 0;
    context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
    context->IASetInputLayout(m_SpriteInputLayout.Get());
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    context->VSSetShader(m_SpriteVertexShader.Get(), nullptr, 0);
    context->PSSetShader(m_SpritePixelShader.Get(), nullptr, 0);
    context->PSSetShaderResources(0, 1, &texture);
    context->PSSetSamplers(0, 1, m_SamplerState.GetAddressOf());

    context->Draw(6, 0);
}

bool CRenderer::LoadShaderFromFile(const std::string& file, std::vector<char>& bytecode)
{
    std::ifstream shaderFile(file, std::ios::binary);

    if (!shaderFile)
    {
        return false;
    }

    shaderFile.seekg(0, std::ios::end);
    size_t size = static_cast<size_t>(shaderFile.tellg());
    shaderFile.seekg(0, std::ios::beg);

    bytecode.resize(size);
    shaderFile.read(bytecode.data(), size);

    return true;
}
