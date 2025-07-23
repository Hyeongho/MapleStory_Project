#pragma once

#include "../Component.h"

class CSpriteComponent :
    public CComponent
{
    DECLARE_TYPEINFO(CSpriteComponent, CComponent)

public:
    CSpriteComponent();
    virtual ~CSpriteComponent();

private:
    ID3D11ShaderResourceView* m_Texture = nullptr;
    Vector2 m_Position;
    Vector2 m_Size;

public:
    void SetTexture(ID3D11ShaderResourceView* Tex);
    void SetPosition(const Vector2& Pos);
    void SetSize(const Vector2& Size);

    const Vector2& GetPosition() const 
    { 
        return m_Position; 
    }

    const Vector2& GetSize() const 
    { 
        return m_Size; 
    }

    virtual void Render() override;
};

