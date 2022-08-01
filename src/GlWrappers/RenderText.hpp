#pragma once
#define RENDER_WCHAR
#include "FreeType.hpp"
#define GL_H <GL/glew.h>
#include "render_text.h"
#include <stdexcept>

class RenderText{
private:
    FT_Face face;

    GLuint prog;

    GLint vertexPos;
    GLint texPos;
    GLint colorPos;

    static RenderText* defaul_instance;
    static FT_Face *default_face;
    
public:
    static RenderText* GetDefaultRenderer();
    static void InitDefaultRenderer(const char *font_path, GLuint program);
    RenderText(FT_Face face, GLuint program, const char *attribVertexName = "vertex_p", const char *uniformTextureName = "tex", const char *uniformTextColor3f = "color");
    GLuint GetProgram() const noexcept;
    void Render(const __CH_TYPE_ *text, int space, int fontSize, int x, int y, float r = 0.6666, float g = 0.6666, float b = 1.0) const noexcept;
    int GetTextWidth(const __CH_TYPE_ *text, int space, int fontSize) const noexcept;
};
