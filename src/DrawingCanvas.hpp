#pragma once
#include <memory>
#include "UnicodeWindows.hpp"
#include "Texture.hpp"
#include "Framebuffer.hpp"
#include <glad/glad.h>

class DrawingCanvas
{
private:
    Texture &bg;
    std::unique_ptr<Texture> currState;
    Framebuffer frameBuffer;
    GLuint drawImageProgram;
    GLint drawImageVertexP;
    GLint drawImageTex;

    int cx, cy;
public:
    const Texture &GetBackground() const noexcept;
    DrawingCanvas(Texture &bg);
    ~DrawingCanvas() noexcept;
    void OnShow(int cx, int cy);
    void Draw();
};
