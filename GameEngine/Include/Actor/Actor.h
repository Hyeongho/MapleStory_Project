#pragma once

#include "../Object/Object.h"

class CComponent;

class CActor :
    public CObject
{
    DECLARE_TYPEINFO(CActor, CObject)

public:
    CActor();
    virtual ~CActor();

private:
    std::vector<TSharedPtr<CComponent>> m_Components;

public:
    // 컴포넌트 추가
    void AddComponent(const TSharedPtr<CComponent>& Component);

    // 전체 컴포넌트 접근
    const std::vector<TSharedPtr<CComponent>>& GetComponents() const;

    // 매 프레임 업데이트
    virtual void Tick(float DeltaTime) override;

    // 렌더 함수
    virtual void Render();

public:
    template <typename T>
    T* GetComponent() const
    {
        for (const auto& comp : m_Components)
        {
            if (IsValid(comp) && IsA<T>(comp.Get()))
            {
                return static_cast<T*>(comp.Get());
            }
        }

        return nullptr;
    }

    /*template <typename T>
    TSharedPtr<T> GetComponentShared() const
    {
        for (const auto& comp : m_Components)
        {
            TSharedPtr<T> casted = Cast<T>(comp);

            if (IsValid(casted))
            {
                return casted;
            }
        }

        return nullptr;
    }*/
};

