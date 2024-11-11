#pragma once

#include "../UI.h"
#include "Math/Vec3.h"

class UIFrame : public UI{
public:
    UIFrame(class Gui* gui) : UI(gui), m_Color(1.0f, 1.0f, 1.0f) {m_UIType = UIType::Frame;}
    ~UIFrame(){}
    
    Vec3<float> m_Color;
private:

};