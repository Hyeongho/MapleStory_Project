#pragma once

#include "../EngineInfo.h"
#include "../Object/Object.h"

class CActor;

class CComponent :
    public CObject
{
    DECLARE_TYPEINFO(CComponent, CObject)

public:
    CComponent();
    virtual ~CComponent();

    void SetOwner(CActor* Owner) 
    { 
        m_Owner = Owner; 
    }

    CActor* GetOwner() const 
    { 
        return m_Owner; 
    }

    virtual void Tick(float DeltaTime) override;

protected:
    CActor* m_Owner = nullptr;
};

