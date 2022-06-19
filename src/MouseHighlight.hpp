#pragma once
#include "ShaderProgram.hpp"

class MouseHighlight{
private:
    static MouseHighlight *renderer;

    GLuint prog;
    GLuint VBO;

    GLint posPos;
    GLint colorPos;
    GLint max_darknessPos;
    GLint powerPos;
    GLint untouched_rdiusPos;
    GLint vertex_pPos;
public:
    static const MouseHighlight &GetRenderer() noexcept;
    static void Init() noexcept;

    MouseHighlight() noexcept;
    ~MouseHighlight() noexcept;
    void Draw(float x, float y, float r, float g, float b, float maxDarkness, float power, float untouchedRadius) const noexcept;
};
