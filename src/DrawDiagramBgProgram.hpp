#pragma once
#include "GL/glew.h"

class DrawDiagramBgProgram{
private:
    GLuint program;

    GLint vertex_p;
    GLint scale;
    GLint translate;
    GLint color;
    GLint vp_size;

    GLuint VBO;
public:
    DrawDiagramBgProgram(GLuint program) noexcept;

    void Draw(int posX, int posY, int textWidth, int fontSize, float r, float g, float b) const noexcept;
    virtual ~DrawDiagramBgProgram() noexcept;
};