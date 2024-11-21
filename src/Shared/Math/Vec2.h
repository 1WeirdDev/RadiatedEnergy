#pragma once

//TODO: More static asserts for easier error messages

template<typename TYPE>
class Vec2{
public:
    TYPE m_X = static_cast<TYPE>(0);
    TYPE m_Y = static_cast<TYPE>(0);

    Vec2(){}
    Vec2(TYPE value):
        m_X(value),
        m_Y(value){
        static_assert(std::is_arithmetic<TYPE>::value, "TYPE must be a numeric type");
    }

    Vec2(TYPE x, TYPE y):
        m_X(x),
        m_Y(y){
        static_assert(std::is_arithmetic<TYPE>::value, "TYPE must be a numeric type");
    }

    void SetData(TYPE x, TYPE y) noexcept{
        m_X = x;
        m_Y = y;
    }
public:
    //TODO: make only available for type float/double
    void Normalize() noexcept{
        TYPE mag = GetMagnitude();
        if(mag <= 1)return;
        m_X /= mag;
        m_Y /= mag;
    }

    Vec2<TYPE> GetNormalized() const noexcept{
        TYPE mag = GetMagnitude();
        if(mag <= 1)return;
        return Vec2<TYPE>(m_X / mag, m_Y / mag);
    }
    template<typename T>
    T GetMagnitude() const noexcept{return static_cast<T>(sqrt(m_X * m_X + m_Y * m_Y));}
    TYPE GetMagnitude() const noexcept{return static_cast<TYPE>(sqrt(m_X * m_X + m_Y * m_Y));}

    template<typename T>
    T GetDotProduct(const Vec2<TYPE> rhs) const noexcept{return static_cast<T>(m_X * rhs.m_X + m_Y * rhs.m_Y);}
    TYPE GetDotProduct(const Vec2<TYPE> rhs) const noexcept{return static_cast<TYPE>(m_X * rhs.m_X + m_Y * rhs.m_Y);}
public:
    //Operators

    Vec2<TYPE> operator-()const noexcept{
        return Vec2<TYPE>(-m_X, -m_Y);
    }

    bool operator<(const Vec2<TYPE>& other) const noexcept{
        if(m_X == other.m_X)
            return m_Y < other.m_Y;
        return m_X < other.m_X;
    }

    Vec2<TYPE> operator+=(const Vec2<TYPE> rhs) noexcept{
        m_X += rhs.m_X;
        m_Y += rhs.m_Y;
        return *this;
    }
    Vec2<TYPE> operator-=(const Vec2<TYPE> rhs) noexcept{
        m_X -= rhs.m_X;
        m_Y -= rhs.m_Y;
        return *this;
    }
    Vec2<TYPE> operator*=(const Vec2<TYPE> rhs) noexcept{
        m_X *= rhs.m_X;
        m_Y *= rhs.m_Y;
        return *this;
    }
    Vec2<TYPE> operator/=(const Vec2<TYPE> rhs) noexcept{
        m_X /= rhs.m_X;
        m_Y /= rhs.m_Y;
        return *this;
    }
    Vec2<TYPE> operator*=(TYPE value) noexcept{
        m_X *= value;
        m_Y *= value;
        return *this;
    }
    Vec2<TYPE> operator/=(TYPE value) noexcept{
        m_X /= value;
        m_Y /= value;
        return *this;
    }

    Vec2<TYPE> operator+(const Vec2<TYPE> rhs) const noexcept{
        return Vec2<TYPE>(m_X + rhs.m_X, m_Y + rhs.m_y);
    }
    Vec2<TYPE> operator-(const Vec2<TYPE> rhs) const noexcept{
        return Vec2<TYPE>(m_X - rhs.m_X, m_Y - rhs.m_y);
    }
    Vec2<TYPE> operator*(const Vec2<TYPE> rhs) const noexcept{
        return Vec2<TYPE>(m_X * rhs.m_X, m_Y * rhs.m_y,);
    }
    Vec2<TYPE> operator/(const Vec2<TYPE> rhs) const noexcept{
        return Vec2<TYPE>(m_X / rhs.m_X, m_Y / rhs.m_y);
    }

    inline bool operator==(const Vec2<TYPE>& rhs) const noexcept {
        static_assert(std::is_arithmetic<TYPE>::value, "TYPE must be a numeric type");
        return rhs.m_X == m_X && rhs.m_Y == m_Y;
    }
    inline bool operator!=(const Vec2<TYPE>& rhs) const noexcept{
        return rhs.m_X != m_X || rhs.m_Y != m_Y;
    }
};