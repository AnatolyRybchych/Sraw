#include "DrawImage.hpp"
#include "ResourceProvider.hpp"

DrawImage *DrawImage::renderer = nullptr;

void DrawImage::Init() noexcept{
    if(renderer != nullptr) delete renderer;
    renderer = new DrawImage();
}

const DrawImage &DrawImage::GetRenderer() noexcept{
    return *renderer;
}

DrawImage::DrawImage() noexcept{
    prog = ResourceProvider::GetProvider().GetDrawImageProgram();
    drawImageVertexP = glGetAttribLocation(prog, "vertex_p");
    drawImageTex = glGetUniformLocation(prog, "tex");

    float vertices[] = {
        -1, 1, 1, -1, 1, 1,
        -1, 1, 1, -1, -1, -1
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DrawImage::Draw(GLuint texture) const noexcept{
    glUseProgram(prog);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(drawImageTex, 0);

    glEnableVertexAttribArray(drawImageVertexP);
    glVertexAttribPointer(drawImageVertexP, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(drawImageVertexP);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}

DrawImage::~DrawImage() noexcept{
    glDeleteProgram(prog);
    glDeleteBuffers(1, &VBO);
}

