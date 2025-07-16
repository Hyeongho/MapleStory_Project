#pragma once

#include "../Component.h"

class CTransformComponent :
    public CComponent
{
    DECLARE_TYPEINFO(CTransformComponent, CComponent)

public:
    CTransformComponent();
    virtual ~CTransformComponent();

private:
    Vector2 m_Position;
    float m_Rotation = 0.f;
    Vector2 m_Scale;

public:
    virtual void Tick(float DeltaTime) override;

    void SetPosition(const Vector2& Pos) 
    { 
        m_Position = Pos; 
    }

    void SetRotation(float Radians) 
    {
        m_Rotation = Radians; 
    }

    void SetScale(const Vector2& Scale) 
    { 
        m_Scale = Scale; 
    }

    const Vector2& GetPosition() const 
    { 
        return m_Position; 
    }

    float GetRotation() const 
    { 
        return m_Rotation; 
    }

    const Vector2& GetScale() const 
    { 
        return m_Scale; 
    }
};

