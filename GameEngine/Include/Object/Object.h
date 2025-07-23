#pragma once

#include "../EngineInfo.h"

class CObject
{
	DECLARE_ROOT_TYPEINFO(CObject)

public:
    CObject();
    virtual ~CObject() = default;

protected:
    std::string m_Name;
    int m_ID;
    bool m_PendingDestroy = false;
    static int s_NextID;

public:
    void SetName(const std::string& Name) 
    { 
        m_Name = Name; 
    }

    const std::string& GetName() const 
    { 
        return m_Name; 
    }

    int GetID() const 
    { 
        return m_ID; 
    }

    void Destroy();

    bool IsPendingDestroy() const 
    { 
        return m_PendingDestroy; 
    }

    virtual void Tick(float DeltaTime);
    virtual void Render();

};

