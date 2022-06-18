#pragma once
#include "ShaderProgram.hpp"

class DrawImage{
    GLuint prog;

    GLint drawImageVertexP;
    GLint drawImageTex;
    GLuint VBO;
public:
    DrawImage() noexcept;
    void Draw(GLuint texture) const noexcept;
    ~DrawImage() noexcept;
};
