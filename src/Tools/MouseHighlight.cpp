#include "MouseHighlight.hpp"

constexpr const char *MouseHighlightVertex = 
"#version 110\n"
"\n"
"attribute vec4 vertex_p;\n"
"varying vec2 frag_coord;\n"
"\n"
"void main(){\n"
"   frag_coord = vertex_p.xy;\n"
"   gl_Position = vertex_p;\n"
"}\n"
"";

constexpr const char *MouseHighlightFragment = 
"#version 110\n"
"\n"
"varying vec2 frag_coord;\n"
"uniform vec2 pos;\n"
"uniform vec3 color;\n"
"uniform float max_darkness;\n"
"uniform float power;\n"
"uniform float untouched_radius;\n"
"\n"
"void main(){\n"
"   float fragPower = distance(frag_coord, pos) - untouched_radius;\n"
"   fragPower = fragPower >= 0.0 ? fragPower * power : fragPower;\n"
"   fragPower = fragPower > max_darkness ? max_darkness : fragPower;\n"
"   gl_FragColor = vec4(color, fragPower);\n"
"}\n"
"";

MouseHighlight *MouseHighlight::renderer = nullptr;

const MouseHighlight &MouseHighlight::GetRenderer() noexcept{
    return *renderer;
}

void MouseHighlight::Init() noexcept{
    if(renderer != nullptr) delete renderer;
    renderer = new MouseHighlight();
}

MouseHighlight::MouseHighlight() noexcept{
    prog = BuildShaderProgram(MouseHighlightVertex, MouseHighlightFragment);

    posPos = glGetUniformLocation(prog, "pos");
    colorPos = glGetUniformLocation(prog, "color");
    max_darknessPos = glGetUniformLocation(prog, "max_darkness");
    powerPos = glGetUniformLocation(prog, "power");
    untouched_rdiusPos = glGetUniformLocation(prog, "untouched_radius");

    vertex_pPos = glGetAttribLocation(prog, "vertex_p");

    float vertices[] = {
        -1, 1, 1, -1, 1, 1,
        -1, 1, 1, -1, -1, -1
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

MouseHighlight::~MouseHighlight() noexcept{
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(prog);
}

void MouseHighlight::Draw(float x, float y, float r, float g, float b, float maxDarkness, float power, float untouchedRadius)const noexcept{
    glUseProgram(prog);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(vertex_pPos);

    glUniform2f(posPos, x, y);
    glUniform3f(posPos, r, g, b);
    glUniform1f(max_darknessPos, maxDarkness);
    glUniform1f(powerPos, power);
    glUniform1f(untouched_rdiusPos, untouchedRadius);

    glVertexAttribPointer(vertex_pPos, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}
