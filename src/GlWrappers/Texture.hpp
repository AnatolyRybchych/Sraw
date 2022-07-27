#pragma once
#include"..\UnicodeWindows.hpp"
#include <GL/glew.h>


class Texture{
private:
    GLuint glId;
public:
    //creates new texture with bitmap data
    Texture(HBITMAP hbmp);

    //creates new texture with not initialized data
    Texture(int cx, int cy);

    //new instance using initialized texture (will bee freed)
    Texture(GLuint texture);

    //returns opengl id for this object
    GLuint GetGLID() const noexcept;

    //frees opengl texture object
    ~Texture();
};
