#pragma once
#include"UnicodeWindows.hpp"
#include<glad/glad.h>


class Texture{
private:
    GLuint glId;
public:
    Texture(HBITMAP hbmp);
    Texture(int cx, int cy);
    GLuint GetGLID() const noexcept;
    ~Texture();
};
