#include "DrawDiagramBgProgram.hpp"

DrawDiagramBgProgram::DrawDiagramBgProgram(GLuint program) noexcept
:program(program){
    vertex_p = glGetAttribLocation(program, "vertex_p");
    scale = glGetUniformLocation(program, "scale");
    translate = glGetUniformLocation(program, "translate");
    color = glGetUniformLocation(program, "color");
    vp_size = glGetUniformLocation(program, "vp_size");

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    float data[] = {
        -1, 1, 1, -1, 1, 1,
        -1, 1, 1, -1, -1, -1
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

DrawDiagramBgProgram::~DrawDiagramBgProgram() noexcept{
    glDeleteBuffers(1, &VBO);
}

void DrawDiagramBgProgram::Draw(int posX, int posY, int textWidth, int fontSize, float r, float g, float b) const noexcept{
    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    int cx = vp[2];
    int cy = vp[3];

    glUseProgram(program);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(vertex_p);

    glUniform2f(vp_size, cx, cy);
    glUniform2f(scale, (textWidth * 1.5)  / (double)cx, (fontSize * 1.8) / (double)(cy));
    glUniform2f(translate, posX / (double)cx * 2.0 - 1.0,  1.0 - 2.0 * posY / (double)(cy));
    glUniform3f(color, r, g, b);

    glVertexAttribPointer(vertex_p, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(vertex_p);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}