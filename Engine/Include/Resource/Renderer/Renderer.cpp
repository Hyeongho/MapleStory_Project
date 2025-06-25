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
