#include "pch.h"
#include "UIImage.h"

UIImage::UIImage(class Gui* gui) : UI(gui) {m_UIType = UIType::Image; }
UIImage::UIImage(class Gui* gui,  GLuint texture) : UI(gui) {m_UIType = UIType::Image; m_TextureId = texture;}

UIImage::~UIImage(){
}