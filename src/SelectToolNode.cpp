#include "SelectToolNode.hpp"

const int SelectToolNode::MaxToolNodes = 5;
const float SelectToolNode::CircleScale = 0.5;

void SelectToolNode::Select() noexcept{ OnSelect();}

constexpr const char *MenuBgVertex = 
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

constexpr const char *MenuBgFragment = 
"#version 110\n"
"\n"
"uniform float circle_scale;\n"
"uniform vec2 viewport;\n"
"varying vec2 frag_coord;\n"
"\n"
"void main(){\n"
"   float alpha = clamp((1.0 - distance(frag_coord / vec2((viewport.y / viewport.x) * circle_scale,  circle_scale), vec2(0, 0))) * viewport.y * 0.5, 0.5, 0.8);\n"
"   gl_FragColor = vec4(0.0, 0.0, 0.0, alpha);\n"
"}\n"
"";

void SelectToolNode::DrawSelectToolMenuBG(int cx, int cy) const noexcept{
    glUseProgram(prog);
    glEnableVertexAttribArray(vertex_pPos);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glUniform2f(viewportPos, (float)cx, (float)cy);
    glUniform1f(circle_scalePos, CircleScale);

    glVertexAttribPointer(vertex_pPos, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(vertex_pPos);
    glUseProgram(0);
}

void SelectToolNode::Draw(int cx, int cy, int pos, bool mouseOver) noexcept{

}

void SelectToolNode::DrawSelectToolMenu(int cx, int cy, int mouseOverTool) noexcept{
    DrawSelectToolMenuBG(cx, cy);
    for(int i = 0 ; i < GetToolNodes().size(); i++)
        GetToolNodes()[i]->Draw(cx, cy, i, i == mouseOverTool);
}

SelectToolNode::SelectToolNode() noexcept{
    float vertices[] = {
        -1, 1, 1, -1, 1, 1,
        -1, 1, 1, -1, -1, -1
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    prog = BuildShaderProgram(MenuBgVertex, MenuBgFragment);
    vertex_pPos = glGetAttribLocation(prog, "vertex_p");
    viewportPos = glGetUniformLocation(prog, "viewport");
    circle_scalePos = glGetUniformLocation(prog, "circle_scale");
}

SelectToolNode::~SelectToolNode() noexcept{
    glDeleteProgram(prog);
}
