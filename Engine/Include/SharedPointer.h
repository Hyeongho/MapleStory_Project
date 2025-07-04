#pragma once

class RefCountBase
{
public:
    int StrongCount = 1;
    int WeakCount = 0;

    void AddStrong() 
    { 
        StrongCount++; 
    }

    void ReleaseStrong() 
    { 
        StrongCount--; 
    }

    void AddWeak()
    { 
        WeakCount++; 
    }

    void ReleaseWeak()
    { 
        WeakCount--; 
    }

    bool IsExpired() const 
    { 
        return StrongCount == 0; 
    }
};

template<typename T>
class TWeakPtr;

template<typename T>
class TSharedPtr;

// TSharedFromThis base class
template<typename T>
class TSharedFromThis
{
protected:
    mutable TWeakPtr<T> WeakThis;

public:
    TSharedPtr<T> AsShared() const
    {
        return WeakThis.Lock();
    }

    friend class TSharedPtr<T>;
};

// TSharedPtr

template<typename T>
class TSharedPtr
{
private:
    T* Ptr = nullptr;
    RefCountBase* Counter = nullptr;

    void InitializeWeakThis()
    {
        if constexpr (std::is_base_of<TSharedFromThis<T>, T>::value)
        {
            Ptr->WeakThis = TWeakPtr<T>(*this);
        }
    }

public:
    TSharedPtr() = default;

    explicit TSharedPtr(T* InPtr) : Ptr(InPtr), Counter(new RefCountBase)
    {
        InitializeWeakThis();
    }

    TSharedPtr(const TSharedPtr& Other) : Ptr(Other.Ptr), Counter(Other.Counter)
    {
        if (Counter)
        {
            Counter->AddStrong();
        }
    }

    TSharedPtr(TSharedPtr&& Other) noexcept : Ptr(Other.Ptr), Counter(Other.Counter)
    {
        Other.Ptr = nullptr;
        Other.Counter = nullptr;
    }

    ~TSharedPtr()
    {
        Reset();
    }

    void Reset()
    {
        if (Counter)
        {
            Counter->ReleaseStrong();

            if (Counter->StrongCount == 0)
            {
                delete Ptr;

                if (Counter->WeakCount == 0)
                {
                    delete Counter;
                }
            }
        }

        Ptr = nullptr;
        Counter = nullptr;
    }

    TSharedPtr& operator=(const TSharedPtr& Other)
    {
        if (this != &Other)
        {
            Reset();
            Ptr = Other.Ptr;
            Counter = Other.Counter;
            if (Counter)
            {
                Counter->AddStrong();
            }
        }

        return *this;
    }

    TSharedPtr& operator=(TSharedPtr&& Other) noexcept
    {
        if (this != &Other)
        {
            Reset();
            Ptr = Other.Ptr;
            Counter = Other.Counter;
            Other.Ptr = nullptr;
            Other.Counter = nullptr;
        }

        return *this;
    }

    T* Get() const 
    { 
        return Ptr; 
    }

    T* operator->() const 
    { 
        return Ptr; 
    }

    T& operator*() const 
    { 
        return *Ptr; 
    }

    bool IsValid() const 
    { 
        return Ptr != nullptr; 
    }

    int UseCount() const 
    { 
        return Counter ? Counter->StrongCount : 0; 
    }

    friend class TWeakPtr<T>;
};

// MakeShared for convenience
template<typename T, typename... Args>
TSharedPtr<T> MakeShared(Args&&... args)
{
    return TSharedPtr<T>(new T(std::forward<Args>(args)...));
}

// IsValid macro
#define IsValid(Ptr) ((Ptr).IsValid())

// TWeakPtr

template<typename T>
class TWeakPtr
{
private:
    T* Ptr = nullptr;
    RefCountBase* Counter = nullptr;

public:
    TWeakPtr() = default;

    TWeakPtr(const TSharedPtr<T>& Shared) : Ptr(Shared.Ptr), Counter(Shared.Counter)
    {
        if (Counter)
        {
            Counter->AddWeak();
        }
    }

    TWeakPtr(const TWeakPtr& Other) : Ptr(Other.Ptr), Counter(Other.Counter)
    {
        if (Counter)
        {
            Counter->AddWeak();
        }
    }

    TWeakPtr(TWeakPtr&& Other) noexcept : Ptr(Other.Ptr), Counter(Other.Counter)
    {
        Other.Ptr = nullptr;
        Other.Counter = nullptr;
    }

    ~TWeakPtr()
    {
        if (Counter)
        {
            Counter->ReleaseWeak();
            if (Counter->StrongCount == 0 && Counter->WeakCount == 0)
            {
                delete Counter;
            }
        }
    }

    TSharedPtr<T> Lock() const
    {
        if (Counter && Counter->StrongCount > 0)
        {
            return TSharedPtr<T>(*this);
        }

        return TSharedPtr<T>();
    }

    bool IsExpired() const
    {
        return !Counter || Counter->StrongCount == 0;
    }
};
