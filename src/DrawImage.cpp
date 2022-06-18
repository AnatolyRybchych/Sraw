#include "DrawImage.hpp"

constexpr const char *DrawImageVertex = 
"#version 110\n"
"\n"
"attribute vec4 vertex_p;\n"
"varying vec2 tex_coord;\n"
"\n"
"void main(){\n"
"   tex_coord = vertex_p.xy * 0.5 + vec2(0.5, 0.5);\n"
"   gl_Position = vertex_p;\n"
"}\n"
"";

constexpr const char *DrawImageFragment = 
"#version 110\n"
"\n"
"varying vec2 tex_coord;\n"
"uniform sampler2D tex;\n"
"\n"
"void main(){\n"
"   gl_FragColor = texture2D(tex, tex_coord);\n"
"}\n"
"";

DrawImage::DrawImage() noexcept{
    prog = BuildShaderProgram(DrawImageVertex, DrawImageFragment);
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

