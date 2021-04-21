#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "GL.h"
#include "stb_image.h"
#include <iostream>
class TextureLoader
{
public:
    unsigned int TextureFromFile(std::string path);

};
#endif