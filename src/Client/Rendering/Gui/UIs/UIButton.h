#pragma once

#include "../UI.h"

typedef std::function<bool(int button, bool isDown)> MouseButtonCallback;
class UIButton : public UI{
public:
    UIButton(class Gui* gui);
    ~UIButton();

    MouseButtonCallback* AddMouseButtonCallback(MouseButtonCallback callback);

public:
    const std::vector<MouseButtonCallback>& GetMouseButtonCallbacks() const {return m_MouseButtonCallbacks;}
private:
    std::vector<MouseButtonCallback> m_MouseButtonCallbacks;
};