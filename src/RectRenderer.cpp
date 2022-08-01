#include "RectRenderer.hpp"

RectRenderer *RectRenderer::renderer = nullptr;

RectRenderer::RectRenderer() noexcept{
    prog = ResourceProvider::GetProvider().GetFillRectProgram();

    vertex_p = glGetAttribLocation(prog, "vertex_p");
    color = glGetUniformLocation(prog, "color");

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    float vertices[] = {
        -1, 1, 1, -1, 1, 1,
        -1, 1, 1, -1, -1, -1
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const RectRenderer &RectRenderer::GetRenderer() noexcept{
    if(renderer == nullptr) renderer = new RectRenderer();
    return *renderer;
}

RectRenderer::~RectRenderer() noexcept{
    glDeleteBuffers(1, &VBO);
}

void RectRenderer::Fill(float r, float g, float b, float a) const noexcept{
    glUseProgram(prog);
    glUniform4f(color, r, g, b, a);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(vertex_p);
    glVertexAttribPointer(vertex_p, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(vertex_p);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

void RectRenderer::Fill(const Coords &p1, const Coords &p2, float r, float g, float b, float a) const noexcept{
    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    int x, y, cx, cy;
    if(p1.GetXGlPixels() > p2.GetXGlPixels()){
        x = p2.GetXGlPixels();
        cx = p1.GetXGlPixels() - x;
    }
    else{
        x = p1.GetXGlPixels();
        cx = p2.GetXGlPixels() - x;
    }
    if(p1.GetYGlPixels() > p2.GetYGlPixels()){
        y = p2.GetYGlPixels();
        cy = p1.GetYGlPixels() - y;
    }
    else{
        y = p1.GetYGlPixels();
        cy = p2.GetYGlPixels() - y;
    }
    glViewport(x, y, cx, cy);
    Fill(r, g, b, a);
    glViewport(vp[0], vp[1], vp[2], vp[3]);
}

