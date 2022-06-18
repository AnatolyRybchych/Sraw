#pragma once
#include <glad/glad.h>

class Framebuffer{
private:
    GLuint glId;
public:
    GLuint GetGLId() const noexcept;
    Framebuffer() noexcept;
    void Bind() const noexcept;
    void Unbind() const noexcept;
    void AttachTexture2D(GLuint texture) const noexcept;
    ~Framebuffer() noexcept;
};
