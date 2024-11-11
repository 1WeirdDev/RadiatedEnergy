#pragma once

template <typename TYPE>
class Vec4{
public:
    TYPE m_X = static_cast<TYPE>(0);
    TYPE m_Y = static_cast<TYPE>(0);
    TYPE m_Z = static_cast<TYPE>(0);
    TYPE m_W = static_cast<TYPE>(0);
public:
    Vec4() noexcept{}
    Vec4(TYPE vals){
        m_X = vals;
        m_Y = vals;
        m_Z = vals;
        m_W = vals;
    }
    Vec4(TYPE x, TYPE y, TYPE z, TYPE w) noexcept{
        m_X = x;
        m_Y = y;
        m_Z = z;
        m_W = w;
    }

    void SetData(TYPE x, TYPE y, TYPE z, TYPE w) noexcept{
        m_X = x;
        m_Y = y;
        m_Z = z;
        m_W = w;
    }
    Vec4<TYPE> operator-() const noexcept{
        Vec4<TYPE> vec(-m_X, -m_Y, -m_Z, -m_W);
        return vec;
    }
    Vec4<TYPE> operator+(const Vec4<TYPE>& rhs) const noexcept{             
        Vec4<TYPE> vec;              
        vec.m_X = m_X + rhs.m_X;
        vec.m_Y = m_Y + rhs.m_Y;
        vec.m_Z = m_Z + rhs.m_Z;
        vec.m_W = m_W + rhs.m_W;
        return vec;
    }
    Vec4<TYPE> operator-(const Vec4<TYPE>& rhs) const noexcept{             
        Vec4<TYPE> vec;              
        vec.m_X = m_X - rhs.m_X;
        vec.m_Y = m_Y - rhs.m_Y;
        vec.m_Z = m_Z - rhs.m_Z;
        vec.m_W = m_W - rhs.m_W;
        return vec;
    }
    Vec4<TYPE> operator/(const Vec4<TYPE>& rhs) const noexcept
    {             
        Vec4<TYPE> vec;              
        vec.m_X = m_X / rhs.m_X;
        vec.m_Y = m_Y / rhs.m_Y;
        vec.m_Z = m_Z / rhs.m_Z;
        vec.m_W = m_W / rhs.m_W;
        return vec;
    }
    Vec4<TYPE> operator*(const Vec4<TYPE>& rhs) const noexcept
    {             
        Vec4<TYPE> vec;              
        vec.m_X = m_X * rhs.m_X;
        vec.m_Y = m_Y * rhs.m_Y;
        vec.m_Z = m_Z * rhs.m_Z;
        vec.m_W = m_W * rhs.m_W;
        return vec;
    }
    Vec4<TYPE> operator*(TYPE scalar) const noexcept
    {             
        Vec4<TYPE> vec(m_X * scalar, m_Y * scalar, m_Z * scalar, m_Z * scalar);   
        return vec;
    }
    Vec4<TYPE>& operator/=(const Vec4<TYPE>& rhs)
    {                           
        m_X /= rhs.m_X;
        m_Y /= rhs.m_Y;
        m_Z /= rhs.m_Z;
        m_W /= rhs.m_W;
        return *this;
    }
    Vec4<TYPE>& operator*=(const Vec4<TYPE>& rhs)
    {                           
        m_X *= rhs.m_X;
        m_Y *= rhs.m_Y;
        m_Z *= rhs.m_Z;
        m_W *= rhs.m_W;
        return *this; // return the result by reference
    }
    Vec4<TYPE>& operator+=(const Vec4<TYPE>& rhs)
    {                           
        m_X += rhs.m_X;
        m_Y += rhs.m_Y;
        m_Z += rhs.m_Z;
        m_W += rhs.m_W;
        return *this; // return the result by reference
    }

    Vec4<TYPE> GetNormalized() const noexcept{
        TYPE magnitude = GetMagnitude();
        if(magnitude == 0.0f)return Vec4<float>(0.0f);
        Vec4<TYPE> vec(m_X / magnitude, m_Y / magnitude, m_Z / magnitude, m_W / magnitude);
        return vec;
    }
    TYPE GetDistance(Vec4<TYPE>& other) const noexcept{
        TYPE xs = other.m_X - m_X;
        TYPE ys = other.m_Y - m_Y;
        TYPE zs = other.m_Z - m_Z;
        TYPE ws = other.m_W - m_W;
        return (TYPE)(xs*2 + ys*2 + zs*2 + ws*2);
    }
    TYPE GetMagnitude() const noexcept{return (TYPE)sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W * m_W);}
};