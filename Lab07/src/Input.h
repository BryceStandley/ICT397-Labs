#pragma once

#include "Texture.h"
class Input
{
public:
    virtual bool KeyPress(GLFWwindow* win, int key) { return false; }
    virtual bool MouseMove() { return false; }
};