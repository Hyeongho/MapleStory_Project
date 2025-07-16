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
    // ������Ʈ �߰�
    void AddComponent(const TSharedPtr<CComponent>& Component);

    // ��ü ������Ʈ ����
    const std::vector<TSharedPtr<CComponent>>& GetComponents() const;

    // �� ������ ������Ʈ
    virtual void Tick(float DeltaTime) override;
};

