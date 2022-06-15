#pragma once
#include "UnicodeWindows.hpp"
#include <glad/glad.h>

class DrawingCanvas
{
private:
    HBITMAP bg;
    int cx, cy;

    GLuint bgTexture;
    GLuint drawImageProgram;

    GLint drawImageVertexP;
    GLint drawImageTex;

    void DrawBG() const noexcept;
public:
    DrawingCanvas(int cx, int cy, HBITMAP bg);
    ~DrawingCanvas() noexcept;
    void Draw();
};
