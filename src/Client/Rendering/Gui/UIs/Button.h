#pragma once

#include "../UI.h"

typedef std::function<bool(int button, bool isDown)> MouseButtonCallback;
class Button : public UI{
public:
    Button(class Gui* gui);
    ~Button();

    MouseButtonCallback* AddMouseButtonCallback(MouseButtonCallback callback);

public:
    const std::vector<MouseButtonCallback>& GetMouseButtonCallbacks() const {return m_MouseButtonCallbacks;}
private:
    std::vector<MouseButtonCallback> m_MouseButtonCallbacks;
};