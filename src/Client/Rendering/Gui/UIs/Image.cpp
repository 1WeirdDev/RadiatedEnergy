#include "pch.h"
#include "Image.h"

Image::Image(class Gui* gui) : UI(gui) {m_UIType = UT_Image; }
Image::Image(class Gui* gui,  GLuint texture) : UI(gui) {m_UIType = UT_Image; m_TextureId = texture;}

Image::~Image(){
    DeleteChildren();
}