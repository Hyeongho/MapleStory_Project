#include "SpriteComponent.h"

#include "../../Engine.h"

#include "../../Resource/Renderer/Renderer.h"
#include "../TransformComponent/TransformComponent.h"
#include "../../Actor/Actor.h"

CSpriteComponent::CSpriteComponent() : m_Position(0.f, 0.f), m_Size(100.f, 100.f)
{
}

CSpriteComponent::~CSpriteComponent()
{
}

void CSpriteComponent::SetTexture(ID3D11ShaderResourceView* Tex)
{
    m_Texture = Tex;
}

void CSpriteComponent::SetPosition(const Vector2& Pos)
{
    m_Position = Pos;
}

void CSpriteComponent::SetSize(const Vector2& Size)
{
    m_Size = Size;
}

void CSpriteComponent::Render()
{
    CRenderer* renderer = CEngine::GetInst()->GetRenderer();

    if (!m_Texture || !m_Owner) 
    {
        return;
    }

    // 텍스처가 있으면 DrawSprite 사용
    if (m_Texture)
    {
        Vector2 position;

        auto transform = m_Owner->GetComponent<CTransformComponent>();
        if (transform)
        {
            position = transform->GetPosition();
        }

        renderer->DrawSprite(m_Texture, position, m_Size);
    }

    else
    {
        // 텍스처 없으면 삼각형 출력
        renderer->Render();
    }
}
