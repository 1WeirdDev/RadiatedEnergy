#pragma once

//TODO: More static asserts for easier error messages

template<typename TYPE>
class Vec3{
public:
    TYPE m_X = static_cast<TYPE>(0);
    TYPE m_Y = static_cast<TYPE>(0);
    TYPE m_Z = static_cast<TYPE>(0);

    Vec3(){}
    Vec3(TYPE value):
        m_X(value),
        m_Y(value),
        m_Z(value){
        static_assert(std::is_arithmetic<TYPE>::value, "TYPE must be a numeric type");
    }

    Vec3(TYPE x, TYPE y):
        m_X(x),
        m_Y(y),
        m_Z(0){
        static_assert(std::is_arithmetic<TYPE>::value, "TYPE must be a numeric type");
    }

    Vec3(TYPE x, TYPE y, TYPE z):
        m_X(x),
        m_Y(y),
        m_Z(z){
        static_assert(std::is_arithmetic<TYPE>::value, "TYPE must be a numeric type");
    }

    template<typename T>
    T GetMagnitude() const noexcept{return static_cast<T>(sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z));}
    TYPE GetMagnitude() const noexcept{return static_cast<TYPE>(sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z));}

    template<typename T>
    T GetDotProduct(const Vec3<TYPE> rhs) const noexcept{return static_cast<T>(m_X * rhs.m_X + m_Y * rhs.m_Y + m_Z * rhs.m_Z);}
    TYPE GetDotProduct(const Vec3<TYPE> rhs) const noexcept{return static_cast<TYPE>(m_X * rhs.m_X + m_Y * rhs.m_Y + m_Z * rhs.m_Z);}
    
    Vec3<TYPE> operator+=(const Vec3<TYPE> rhs) noexcept{
        m_X += rhs.m_X;
        m_Y += rhs.m_Y;
        m_Z += rhs.m_Z;
        return *this;
    }
    Vec3<TYPE> operator-=(const Vec3<TYPE> rhs) noexcept{
        m_X -= rhs.m_X;
        m_Y -= rhs.m_Y;
        m_Z -= rhs.m_Z;
        return *this;
    }
    Vec3<TYPE> operator*=(const Vec3<TYPE> rhs) noexcept{
        m_X *= rhs.m_X;
        m_Y *= rhs.m_Y;
        m_Z *= rhs.m_Z;
        return *this;
    }
    Vec3<TYPE> operator/=(const Vec3<TYPE> rhs) noexcept{
        m_X /= rhs.m_X;
        m_Y /= rhs.m_Y;
        m_Z /= rhs.m_Z;
        return *this;
    }
    Vec3<TYPE> operator*=(TYPE value) noexcept{
        m_X *= value;
        m_Y *= value;
        m_Z *= value;
        return *this;
    }
    Vec3<TYPE> operator/=(TYPE value) noexcept{
        m_X /= value;
        m_Y /= value;
        m_Z /= value;
        return *this;
    }

    Vec3<TYPE> operator+(const Vec3<TYPE> rhs) const noexcept{
        return Vec3<TYPE>(m_X + rhs.m_X, m_Y + rhs.m_y, m_Z + rhs.m_Z);
    }
    Vec3<TYPE> operator-(const Vec3<TYPE> rhs) const noexcept{
        return Vec3<TYPE>(m_X - rhs.m_X, m_Y - rhs.m_y, m_Z - rhs.m_Z);
    }
    Vec3<TYPE> operator*(const Vec3<TYPE> rhs) const noexcept{
        return Vec3<TYPE>(m_X * rhs.m_X, m_Y * rhs.m_y, m_Z * rhs.m_Z);
    }
    Vec3<TYPE> operator/(const Vec3<TYPE> rhs) const noexcept{
        return Vec3<TYPE>(m_X / rhs.m_X, m_Y / rhs.m_y, m_Z / rhs.m_Z);
    }

    inline bool operator==(const Vec3<TYPE>& rhs) const noexcept {
        static_assert(std::is_arithmetic<TYPE>::value, "TYPE must be a numeric type");
        return rhs.m_X == m_X && rhs.m_Y == m_Y && rhs.m_z == m_Z;
    }
    inline bool operator!=(const Vec3<TYPE>& rhs) const noexcept{
        return rhs.m_X != m_X || rhs.m_Y != m_Y || rhs.m_Z != m_Z;
    }
};