#pragma once

#include <cmath>

// 2D ∫§≈Õ ±∏¡∂√º
struct Vector2
{
    float x = 0.f;
    float y = 0.f;

    Vector2() = default;
    Vector2(float xVal, float yVal) : x(xVal), y(yVal) 
    {

    }

    Vector2 operator+(const Vector2& other) const 
    { 
        return Vector2(x + other.x, y + other.y); 
    }

    Vector2 operator-(const Vector2& other) const 
    { 
        return Vector2(x - other.x, y - other.y); 
    }

    Vector2 operator*(float scalar) const 
    { 
        return Vector2(x * scalar, y * scalar); 
    }

    Vector2 operator/(float scalar) const 
    { 
        return Vector2(x / scalar, y / scalar); 
    }

    Vector2& operator+=(const Vector2& other) 
    { 
        x += other.x; 
        y += other.y; 
        return *this; 
    }

    Vector2& operator-=(const Vector2& other) 
    { 
        x -= other.x; 
        y -= other.y; 
        return *this; 
    }

    Vector2& operator*=(float scalar) 
    { 
        x *= scalar; 
        y *= scalar; 
        return *this; 
    }

    Vector2& operator/=(float scalar) 
    { 
        x /= scalar; 
        y /= scalar; 
        return *this; 
    }

    float Length() const 
    { 
        return std::sqrtf(x * x + y * y);
    }

    float LengthSquared() const 
    { 
        return x * x + y * y; 
    }

    void Normalize()
    {
        float len = Length();

        if (len != 0.f)
        {
            x /= len;
            y /= len;
        }
    }

    static float Dot(const Vector2& a, const Vector2& b)
    {
        return a.x * b.x + a.y * b.y;
    }
};
