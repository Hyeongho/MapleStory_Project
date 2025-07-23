#pragma once

#include "../../EngineInfo.h"

class CRenderer
{
public:
    CRenderer();
    ~CRenderer();

    bool Init();
    void Render();
    void DrawSprite(ID3D11ShaderResourceView* texture, const Vector2& position, const Vector2& size);

private:
    bool LoadShaderFromFile(const std::string& file, std::vector<char>& bytecode);

private:
    ComPtr<ID3D11Buffer> m_VertexBuffer;
    ComPtr<ID3D11InputLayout> m_InputLayout;
    ComPtr<ID3D11VertexShader> m_VertexShader;
    ComPtr<ID3D11PixelShader> m_PixelShader;

    // 스프라이트 렌더용
    ComPtr<ID3D11InputLayout> m_SpriteInputLayout;
    ComPtr<ID3D11VertexShader> m_SpriteVertexShader;
    ComPtr<ID3D11PixelShader> m_SpritePixelShader;
    ComPtr<ID3D11SamplerState> m_SamplerState;
};

