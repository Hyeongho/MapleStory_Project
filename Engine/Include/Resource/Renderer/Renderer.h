#pragma once

#include "../../EngineInfo.h"

class CRenderer
{
public:
    CRenderer();
    ~CRenderer();

    bool Init();
    void Render();

private:
    bool LoadShaderFromFile(const std::string& file, std::vector<char>& bytecode);

private:
    ComPtr<ID3D11Buffer> m_VertexBuffer;
    ComPtr<ID3D11InputLayout> m_InputLayout;
    ComPtr<ID3D11VertexShader> m_VertexShader;
    ComPtr<ID3D11PixelShader> m_PixelShader;
};

