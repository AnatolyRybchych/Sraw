#include "Framebuffer.hpp"

Framebuffer::Framebuffer() noexcept{
    glGenFramebuffers(1, &glId);
}

void Framebuffer::Bind() const noexcept{
    glBindFramebuffer(GL_FRAMEBUFFER, glId);
}

void Framebuffer::Unbind() const noexcept{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::AttachTexture2D(GLuint texture) const noexcept{
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
}

Framebuffer::~Framebuffer() noexcept{
    glDeleteFramebuffers(1, &glId);
}
