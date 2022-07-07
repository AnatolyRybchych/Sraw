#include "RenderText.hpp"
#include "ShaderProgram.hpp"

RenderText::RenderText(FT_Face face, const char *attribVertexName, const char *uniformTextureName, const char *vertex, const char *fragment){
    this->face = face;
    prog = BuildShaderProgram(vertex, fragment);
    vertexPos = glGetAttribLocation(prog, attribVertexName);
    texPos = glGetUniformLocation(prog, uniformTextureName);
}

GLuint RenderText::GetProgram() const noexcept{
    return prog;
}

void RenderText::Render(const char *text, int space, int fontSize, point pos, viewport viewport) const noexcept{
    FT_Set_Pixel_Sizes(face, 0, fontSize);

    render_text(face, text, space, pos, &viewport, vertexPos, texPos);
}
