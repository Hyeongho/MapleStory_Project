#pragma once

#include <cassert>
#include <cstddef>
#include <type_traits>

#include "SharedPointer.h"

// Ÿ�� ������ �����ϴ� ����ü (�̸� + �θ� ������)
class CTypeInfo
{
public:
    const char* Name;             // Ŭ���� �̸�
    const CTypeInfo* SuperType;  // �θ� Ÿ�� ����

    constexpr CTypeInfo(const char* InName, const CTypeInfo* InSuper) : Name(InName), SuperType(InSuper) 
    {
    }

    // �� Ÿ���� Target Ÿ������, Ȥ�� ��� ������ ���ԵǴ��� Ȯ��
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

// Ÿ�� ������ ����ϴ� ��ũ��
#define DECLARE_TYPEINFO(ClassName, SuperClassName) \
public: \
    static constexpr CTypeInfo StaticTypeInfo{ #ClassName, &SuperClassName::StaticTypeInfo }; \
    virtual const CTypeInfo* GetTypeInfo() const { return &StaticTypeInfo; } \
private:

// ��Ʈ Ŭ������ ��ũ�� (�θ� ����)
#define DECLARE_ROOT_TYPEINFO(ClassName) \
public: \
    static constexpr CTypeInfo StaticTypeInfo{ #ClassName, nullptr }; \
    virtual const CTypeInfo* GetTypeInfo() const { return &StaticTypeInfo; } \
private:

// IsA: ��ü�� Ư�� Ÿ���̰ų�, �� �ڽ� Ÿ������ �˻�
template<typename To, typename From>
bool IsA(From* Object)
{
    if (Object == nullptr)
    {
        return false;
    }

    return Object->GetTypeInfo()->IsA(&To::StaticTypeInfo);
}

// Cast: Ÿ���� ������ ��ȯ, Ʋ���� nullptr ��ȯ
template<typename To, typename From>
To* Cast(From* Object)
{
    if (IsA<To>(Object))
    {
        return static_cast<To*>(Object);
    }

    return nullptr;
}

// CastChecked: �ݵ�� ��ȯ �����ؾ� ��, Ʋ���� assert
template<typename To, typename From>
To* CastChecked(From* Object)
{
    To* Result = Cast<To>(Object);
    assert(Result && "CastChecked failed: Ÿ���� ��ġ���� �ʽ��ϴ�.");
    return Result;
}

// StaticCast: �������� ������ ����
template<typename To, typename From>
To* StaticCast(From* Object)
{
    return (To*)(Object);
}

// ConstCast: const ���� ĳ����
template<typename To, typename From>
To* ConstCast(From* Object)
{
    return (To*)(const_cast<std::remove_const_t<From>*>(Object));
}

// ����Ʈ ������ ĳ���� ����

// Cast: SharedPtr<T> ���� ������ ĳ����
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

// CastChecked: SharedPtr<T> ����, ���� �� assert
template<typename To, typename From>
TSharedPtr<To> CastChecked(const TSharedPtr<From>& Object)
{
    TSharedPtr<To> Result = Cast<To>(Object);
    assert(IsValid(Result) && "CastChecked failed: Ÿ���� ��ġ���� �ʽ��ϴ�.");
    return Result;
}

// Cast: WeakPtr<T> ĳ���� ����
template<typename To, typename From>
TWeakPtr<To> Cast(const TWeakPtr<From>& Object)
{
    if (IsValid(Object))
    {
        return nullptr;
    }

    return Cast<To>(Object.Pin()); // Pin �� SharedPtr �������� ����
}

// CastChecked: WeakPtr<T> ����, ���� �� assert
template<typename To, typename From>
TWeakPtr<To> CastChecked(const TWeakPtr<From>& Object)
{
    TSharedPtr<To> Result = CastChecked<To>(Object.Pin());
    return Result; // �Ͻ������� TWeakPtr<To>�� ��ȯ
}

// ���:
// - DECLARE_ROOT_TYPEINFO(): ��Ʈ Ŭ���� ����� (�θ� ����)
// - DECLARE_TYPEINFO(): �ڽ� Ŭ���� ����� (�θ� �ʿ�)
// - IsA<T>(obj): ���� ��ü �˻�
// - Cast<T>(obj): Ÿ�� ������ static_cast, Ʋ���� nullptr
// - CastChecked<T>(obj): Ÿ�� �� ������ assert
// - Cast<T>(SharedPtr): ����Ʈ �����ͳ����� �����ϰ� ��ȯ ����
// - Cast<T>(WeakPtr): ���� ������ �����ϰ� ��ȯ ����