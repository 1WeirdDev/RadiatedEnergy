#pragma once

template<typename ScaleType, typename OffsetType>
class UDim2{
public:
    UDim2():
        m_ScaleX(static_cast<ScaleType>(1)),
        m_ScaleY(static_cast<ScaleType>(1)),
        m_OffsetX(static_cast<OffsetType>(0)),
        m_OffsetY(static_cast<OffsetType>(0)){
    }
    UDim2(ScaleType scaleX, ScaleType scaleY, OffsetType offsetX, OffsetType offsetY):
        m_ScaleX(static_cast<ScaleType>(scaleX)),
        m_ScaleY(static_cast<ScaleType>(scaleY)),
        m_OffsetX(static_cast<OffsetType>(m_OffsetX)),
        m_OffsetY(static_cast<OffsetType>(m_OffsetY)){
    }

    ScaleType m_ScaleX;
    ScaleType m_ScaleY;
    OffsetType m_OffsetX;
    OffsetType m_OffsetY;
};