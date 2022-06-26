#pragma once
#include "GlWrappers/ShaderProgram.hpp"

class DrawImage{
private:    
    GLuint prog;

    GLint drawImageVertexP;
    GLint drawImageTex;
    GLuint VBO;
    DrawImage() noexcept;
    static DrawImage *renderer;
public:
    static void Init() noexcept;
    static const DrawImage &GetRenderer() noexcept;
    void Draw(GLuint texture) const noexcept;
    ~DrawImage() noexcept;
};
