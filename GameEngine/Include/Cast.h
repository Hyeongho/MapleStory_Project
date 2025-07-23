#pragma once

#include <cassert>
#include <cstddef>
#include <type_traits>

#include "SharedPointer.h"

// 타입 정보를 저장하는 구조체 (이름 + 부모 포인터)
class CTypeInfo
{
public:
    const char* Name;             // 클래스 이름
    const CTypeInfo* SuperType;  // 부모 타입 정보

    constexpr CTypeInfo(const char* InName, const CTypeInfo* InSuper) : Name(InName), SuperType(InSuper) 
    {
    }

    // 이 타입이 Target 타입인지, 혹은 상속 계층상 포함되는지 확인
    bool IsA(const CTypeInfo* Target) const
    {
        const CTypeInfo* Current = this;
        while (Current)
        {
            if (Current == Target)
            {
                return true;
            }

            Current = Current->SuperType;
        }

        return false;
    }
};

// 타입 정보를 등록하는 매크로
#define DECLARE_TYPEINFO(ClassName, SuperClassName) \
public: \
    static constexpr CTypeInfo StaticTypeInfo{ #ClassName, &SuperClassName::StaticTypeInfo }; \
    virtual const CTypeInfo* GetTypeInfo() const { return &StaticTypeInfo; } \
private:

// 루트 클래스용 매크로 (부모 없음)
#define DECLARE_ROOT_TYPEINFO(ClassName) \
public: \
    static constexpr CTypeInfo StaticTypeInfo{ #ClassName, nullptr }; \
    virtual const CTypeInfo* GetTypeInfo() const { return &StaticTypeInfo; } \
private:

// IsA: 객체가 특정 타입이거나, 그 자식 타입인지 검사
template<typename To, typename From>
bool IsA(From* Object)
{
    if (Object == nullptr)
    {
        return false;
    }

    return Object->GetTypeInfo()->IsA(&To::StaticTypeInfo);
}

// Cast: 타입이 맞으면 변환, 틀리면 nullptr 반환
template<typename To, typename From>
To* Cast(From* Object)
{
    if (IsA<To>(Object))
    {
        return static_cast<To*>(Object);
    }

    return nullptr;
}

// CastChecked: 반드시 변환 가능해야 함, 틀리면 assert
template<typename To, typename From>
To* CastChecked(From* Object)
{
    To* Result = Cast<To>(Object);
    assert(Result && "CastChecked failed: 타입이 일치하지 않습니다.");
    return Result;
}

// StaticCast: 빠르지만 안전성 낮음
template<typename To, typename From>
To* StaticCast(From* Object)
{
    return (To*)(Object);
}

// ConstCast: const 제거 캐스팅
template<typename To, typename From>
To* ConstCast(From* Object)
{
    return (To*)(const_cast<std::remove_const_t<From>*>(Object));
}

// 스마트 포인터 캐스팅 지원

// Cast: SharedPtr<T> 간의 안전한 캐스팅
template<typename To, typename From>
TSharedPtr<To> Cast(const TSharedPtr<From>& Object)
{
    if (!Object)
    {
        return TSharedPtr<To>(nullptr);
    }

    if (IsA<To>(Object.Get()))
    {
        return TSharedPtr<To>(Object.GetCounter(), static_cast<To*>(Object.Get()));
    }

    return TSharedPtr<To>(nullptr);
}

// CastChecked: SharedPtr<T> 버전, 실패 시 assert
template<typename To, typename From>
TSharedPtr<To> CastChecked(const TSharedPtr<From>& Object)
{
    TSharedPtr<To> Result = Cast<To>(Object);
    assert(IsValid(Result) && "CastChecked failed: 타입이 일치하지 않습니다.");
    return Result;
}

// Cast: WeakPtr<T> 캐스팅 지원
template<typename To, typename From>
TWeakPtr<To> Cast(const TWeakPtr<From>& Object)
{
    if (IsValid(Object))
    {
        return nullptr;
    }

    return Cast<To>(Object.Pin()); // Pin 후 SharedPtr 버전으로 위임
}

// CastChecked: WeakPtr<T> 버전, 실패 시 assert
template<typename To, typename From>
TWeakPtr<To> CastChecked(const TWeakPtr<From>& Object)
{
    TSharedPtr<To> Result = CastChecked<To>(Object.Pin());
    return Result; // 암시적으로 TWeakPtr<To>로 변환
}

// 요약:
// - DECLARE_ROOT_TYPEINFO(): 루트 클래스 선언용 (부모 없음)
// - DECLARE_TYPEINFO(): 자식 클래스 선언용 (부모 필요)
// - IsA<T>(obj): 계층 전체 검사
// - Cast<T>(obj): 타입 맞으면 static_cast, 틀리면 nullptr
// - CastChecked<T>(obj): 타입 안 맞으면 assert
// - Cast<T>(SharedPtr): 스마트 포인터끼리도 안전하게 변환 가능
// - Cast<T>(WeakPtr): 약한 참조도 안전하게 변환 가능